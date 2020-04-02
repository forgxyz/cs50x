#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int shift(char c);

int main(int argc, string argv[])
{
    //check command line inputs
    if (argc != 2)
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
    else
    {
        int len = strlen(argv[1]); //store length of key in variable
        char keyword[len]; //create array to store the keyword
        //key should be alpha only
        for (int i = 0; i < len; i++)
        {
            if (isalpha(argv[1][i]) == 0)
            {
                printf("Usage: ./vigenere keyword\n");
                return 1;
            }
            else
            {
                keyword[i] = tolower(argv[1][i]);
            }
        }

        //collect plaintext string from user
        string plain = get_string("plaintext: \n");
        //declare cipher array of chars for later use; same size as plaintext string
        char cipher[strlen(plain) + 1];

        //iterate over each character in plaintext & modify each letter by the key
        //declare counter variable j to cycle through keyword
        int j = 0;
        for (int i = 0, plen = strlen(plain); i < plen; i++)
        {
            int key = shift(keyword[j]);
            if (isupper(plain[i]) != 0)
            {
                cipher[i] = (char)(((((int)plain[i] - 65) + key) % 26) + 65);
                j++;
            }
            else if (islower(plain[i]) != 0)
            {
                cipher[i] = (char)(((((int)plain[i] - 97) + key) % 26) + 97);
                j++;
            }
            else
            {
                cipher[i] = plain[i];
            }
            //if j is the same length as the keyword reset it to 0
            if (j == strlen(keyword))
            {
                j = 0;
            }
        }
        cipher[(int)strlen(plain)] = '\0';
        printf("ciphertext: %s\n", cipher);
    }
}

//basic shift function to convert lowercsase char key to alphabetical int
int shift (char c)
{
    c = (int)c - 97;
    return c;
}

