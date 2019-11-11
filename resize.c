// Modified from bmp copying function, resizes 24-bit bmp

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize scalingfactor infile outfile\n");
        return 1;
    }

    // remember filenames
    double f = atof(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    int I = bi.biHeight;
    int J = bi.biWidth;
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;


    bi.biWidth = f * bi.biWidth;
    bi.biHeight = f * bi.biHeight;
    int paddingout = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + paddingout) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // enlarge
    if (f >= 1)
    {
        for (int i = 0, biHeight = abs(I); i < biHeight; i++)
        {
            fpos_t x;
            fgetpos(inptr, &x);

            for (int m = 0; m < f; m++)
            {
                fsetpos(inptr, &x);

                // iterate over pixels in scanline
                for (int j = 0; j < J; j++)
                {
                    // temporary storage
                    RGBTRIPLE triple;

                    // read RGB triple from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                    fpos_t y;
                    fgetpos(inptr, &y);
                    for (int n = 0; n < f; n++)
                    {
                        fsetpos(inptr, &y);
                        // write RGB triple to outfile
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
                }

                // skip over padding, if any
                fseek(inptr, padding, SEEK_CUR);

                // then add it back
                for (int k = 0; k < paddingout; k++)
                {
                    fputc(0x00, outptr);
                }
            }
        }
    }
    
    // shrink
    if (f < 1)
    {
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
        {
            // iterate over pixels in scanline
            int count = 2;
            for (int j = 0; j < J; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                if (count % 2 != 0)
                {
                    fflush(inptr);
                }

                // write RGB triple to outfile
                if (count % 2 == 0)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
                count++;
            }

            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);

            // then add it back
            for (int k = 0; k < paddingout; k++)
            {
                fputc(0x00, outptr);
            }
            fseek(inptr, J * 3 + padding, SEEK_CUR);
        }
    }



    // close infile
    fclose(inptr);


    // close outfile
    fclose(outptr);


    // success
    return 0;
}
