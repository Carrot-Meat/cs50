#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    // check for number of args
    if (argc != 2)
    {
        printf("Usage: ./ceaser key\n");
        return 1;
    }
    string key = argv[1];
    // check for int input
    for (int i = 0; i < strlen(key); i++)
    {
        if (isdigit(key[i]) == 0)
        {
            printf("Usage: ./ceaser key\n");
            return 1;
        }
    }

    int k = atoi(argv[1]);
    string p_text = get_string("plaintext:  ");
    string c_text = p_text;
    for (int i = 0; i < strlen(p_text); i++)
    {
        if (64 < c_text[i] && c_text[i] < 91) // uppercase shift
        {
            c_text[i] = (c_text[i] - 65 + k) % 26 + 65;
        }
            
        if (96 < c_text[i] && c_text[i] < 123) // lowercase shift
        {
            c_text[i] = (c_text[i] - 97 + k) % 26 + 97; 
        }
    }
    printf("ciphertext: %s\n", c_text);
}
