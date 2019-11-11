// Detect and sort valid credit card numbers

#include <cs50.h>
#include <stdio.h>

int get_length(long card_number);
string check_valid(long card_number);
int sum_digits(int n);
int get_first_digit(long card_number);
int get_two_digits(long card_number);

int main(void) // Checks for correct length the executes check_valid
{
    long card_number = get_long("Enter credit card number: ");
    int length = get_length(card_number);
    if (length == 13 || length == 15 || length == 16)
    {
        check_valid(card_number);
    }
    else
    {
        printf("INVALID\n");
    }

}
int get_length(long card_number) // Gets length of card number
{
    int counter = 0;
    long n = card_number;
    do 
    {
        counter ++;
        n /= 10;  
    }
    while (n > 0);
    return counter;
}

string check_valid(long card_number) // Checks validity conditions and sorts
{
    long n = card_number;
    int sum = 0;
    // Validates checksum
    do
    {
        sum += n % 10;
        n /= 10;
        sum += sum_digits(2 * (n % 10));
        n /= 10;
    }
    while (n > 0);
    // Begins conditions
    if (sum % 10 == 0)
    {
        if (get_length(card_number) == 13 && get_first_digit(card_number) == 4)
        {
            printf("VISA\n");
            return "VISA\n";
        }

        else if (get_length(card_number) == 16 && get_two_digits(card_number) - 50 >= 1
           && get_two_digits(card_number) - 50 <= 5)
        {
            printf("MASTERCARD\n");
            return "MASTERCARD\n";
        }
        else if (get_length(card_number) == 16 && get_first_digit(card_number) == 4)
        {
            printf("VISA\n");
            return "VISA\n";
        }
        else if (get_length(card_number) == 15 && (get_two_digits(card_number) == 34
           || get_two_digits(card_number) == 37))
        {
            printf("AMEX\n");
            return "AMEX\n";
        } 
    else
    {
    printf("INVALID\n");
    return "INVALID\n";
    }
    }
printf("INVALID\n");
return "INVALID\n";
}

int get_first_digit(long card_number) // Returns first digit of card number
{
    long n = card_number;
    int m;
    while (n > 10)
    {
        n /= 10; 
    }
    m = n;
    return m;  
    
}

int get_two_digits(long card_number) // Returns first two digits of card number
{
    long n = card_number;
    int m;
    while (n > 100)
    {
        n /= 10; 
    }
    m = n;
    return m;  
}

int sum_digits(int n) // Given an integer, sums the digits
{
    int sum = 0;
    do
    {
        sum += n % 10;
        n /= 10;   
    }
    while (n > 0);
    return sum;
}
