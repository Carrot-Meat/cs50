#include <cs50.h>
#include <stdio.h>

int get_1to8(string prompt);
void build_pyramid(int n);

\\ Driver function, asks for integer input, displays "Mario-style" pyramid of correct dimensions
int main(void)
{
    int height = get_1to8("Height: ");
    build_pyramid(height);

}

// Force input of integer between 1 and 8 exclusive
int get_1to8(string prompt)
{
    int n;
    do
    {
        n = get_int("%s", prompt); 
    }
    while (n < 1 || n > 8);
    return n;
}

// Constructs "Mario-style" pyramid
void build_pyramid(int n)
{
 
    for (int i = 0; i < n; i++)
    {
        char c = '#';
        int counter = 1;
        int counter1 = 0;
        printf("%*c", n-i, c);
        while (counter <= i)
        {
            printf("%c", c);
            counter++;
        }

        printf("  ");
        do
        {
            printf("%c", c);
            counter1++;
        }
        while (counter1 <= i);
        printf("\n");
    }
}
