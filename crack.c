// Generate all 5 character a-zA-Z combinations to brute force weak crypt hash password

#include <cs50.h>
#include <stdio.h>
#include <crypt.h>
#include <string.h>

void brute_force(string hash, string salt);
const char ALPHABET[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";
const int LEN = 52;
const long N = 380204032; // 52^5 i.e. ZZZZZ in base 52 using a-zA-Z
int main(int argc, string argv[])
{   
    //get hash and salt
    string hash = argv[1]; 
    char salt[10] = {argv[1][0], argv[1][1]};
    //check args and run brute forcing function
    if (argc != 2)
    {
        printf("incorrect number of command-line arguments given\n");
        return 1;
    }
    brute_force(hash, salt);
    return 0;
}

void brute_force(string hash, string salt)
{
    //set empty array for our strings and start counting 
    char pass[10] = {0, 0, 0, 0, 0}; 
    long count = 0;
    for (int i = 0; i < N; i++)
    {
        long temp = count;
        long temp1 = count;
        int num = 0; 
        // need for trick for reversing string
        while (temp1 > LEN)
        {
            temp1 = temp1 / LEN;
            num++;
        }

        while (temp > 0)
        {   
            // construct a string of count mod 52 using our given characters
            for (int j = num; j > -1; j--)
            {
                pass[j] = ALPHABET[temp % LEN];
                temp = temp / LEN;  
            }
        }
        // check if the hash of our guess matches the inputted hash
        string pword = crypt(pass, salt);
        for (int k = 0; k < 13; k++)
        {
            if (hash[k] != pword[k])
            {
                break;
            }
            if (k == 12)
            {
                printf("%s\n", pass);
                return;
            }
            
        }
                  
        count++;   
    }
 

    
}
