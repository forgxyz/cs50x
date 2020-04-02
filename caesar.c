#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


char convert(char pletter, int key);
int main(int argc, string argv[])
{
    if (argc != 2)
    {
        //if user does not include key in terminal, end program
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        //convert command line key input (string) to integer variable
        int k = atoi(argv[1]);
        //prompt user for plaintext
        string plain = get_string("plaintext: ");
        char cipher[(strlen(plain))];
        //iterate over each character in plaintext
        for (int j = 0, len = strlen(plain); j < len; j++)
        {
            cipher[j] = convert(plain[j], k);
        }
        printf("ciphertext: %s\n", cipher); 
    }
}  
char convert(char pletter, int key)
{
    //function argument will be the plaintext letter, sent here from the above for loop
    //determine if it is a capital, lowercase, or symbol
    if (isupper(pletter) != 0)
    {
        char cletter = (char)((((int) pletter - 65) + key) % 26) + 65;
        return cletter;
    }
    //lowercase at 97
    else if (islower(pletter) != 0)
    {
        char cletter = (char)((((int) pletter - 97) + key) % 26) + 97;
        return cletter;
    }
    //symbols and punctuation should not be altered
    else
    {
        char cletter = pletter;
        return cletter;
    }
}
