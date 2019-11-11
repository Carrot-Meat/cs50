// Identifies and seperates jpg's from data stream

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

const int SIZE = 512;

int main(int argc, char *argv[])
{
    // check for correct usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover imagefile \n");
        return 1;
    }

    // set up input stream
    char *card = argv[1];
    FILE *inptr = fopen(card, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }
    // set up output stream and others
    uint8_t buffer[512];
    int filenum = 0;
    char filename[8];
    FILE *img = NULL;

    while (true)
    {
        // read 512B from input stream
        size_t block = fread(buffer, SIZE, 1, inptr);
        // check for EOF
        if (block != SIZE && feof(inptr))
        {
            return 0;
        }
        // set bool for header
        bool test = buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;
        // if header with open file, close file
        if (test && img != NULL)
        {
            fclose(img);
            filenum++;
        }
        // if header create and open new file
        if (test)
        {
            sprintf(filename, "%03i.jpg", filenum);
            img = fopen(filename, "w");
            if (img == NULL)
            {
                fprintf(stderr, "Could not open %s.\n", filename);
                return 3;
            }
        }
        // else (if not header) and output stream is open, write to image file
        if (img != NULL)
        {
            fwrite(buffer, SIZE, 1, img);
        }
    }
    // close files
    fclose(img);
    fclose(inptr);
    return 0;
}
