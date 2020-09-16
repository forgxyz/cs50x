//October 18 & 22, 2019


#include <cs50.h>
#include <stdio.h>
#include <crypt.h>
#include <stdlib.h>
#include <string.h>

char convert(int x);
bool test(char *x, char *salt, char *hash);

int main(int argc, string argv[])
{
    int LETTERS = 51;
    // argv[1] will be the a user input hashed password

    if (argc != 2)
    {
        printf("usage: ./crack hash\n");
        return 1;
    }
    char *hash = argv[1];

    // store the salt in a variable for later use in testing
    char *salt = malloc(sizeof(char) * 2);
    for (int i = 0; i < 2; i++)
    {
        salt[i] = hash[i];
    }

    //test 1 char string
    for (int i = 0; i < LETTERS; i++)
    {
        //write letter to a char * (note: crypt() will not function properly with a char input)
        char *x = malloc(sizeof(char));
        sprintf(x, "%c", convert(i));
        bool result = test(x, salt, hash);
        if (result)
        {
            printf("%s\n", x);
            free(x);
            free(salt);
            return 0;
        }
        free(x);
    }

    //test 2 char string
    for (int i = 0; i < LETTERS; i++)
    {
        for (int j = 0; j < LETTERS; j++)
        {
            char *x = malloc(sizeof(char));
            sprintf(x, "%c%c", convert(i), convert(j));
            bool result = test(x, salt, hash);
            if (result)
            {
                printf("%s\n", x);
                free(x);
                free(salt);
                return 0;
            }
            free(x);
        }
    }

    //test 3 char string
    for (int i = 0; i < LETTERS; i++)
    {
        for (int j = 0; j < LETTERS; j++)
        {
            for (int k = 0; k < LETTERS; k++)
            {
                char *x = malloc(sizeof(char));
                sprintf(x, "%c%c%c", convert(i), convert(j), convert(k));
                bool result = test(x, salt, hash);
                if (result)
                {
                    printf("%s\n", x);
                    free(x);
                    free(salt);
                    return 0;
                }
                free(x);
            }
        }
    }
    //test 4 char string
    for (int i = 0; i < LETTERS; i++)
    {
        for (int j = 0; j < LETTERS; j++)
        {
            for (int k = 0; k < LETTERS; k++)
            {
                for (int l = 0; l < LETTERS; l++)
                {
                    char *x = malloc(sizeof(char));
                    sprintf(x, "%c%c%c%c", convert(i), convert(j), convert(k), convert(l));
                    bool result = test(x, salt, hash);
                    if (result)
                    {
                        printf("%s\n", x);
                        free(x);
                        free(salt);
                        return 0;
                    }
                    free(x);
                }
            }
        }
    }
    //test 5 char string
    for (int i = 0; i < LETTERS; i++)
    {
        for (int j = 0; j < LETTERS; j++)
        {
            for (int k = 0; k < LETTERS; k++)
            {
                for (int l = 0; l < LETTERS; l++)
                {
                    for (int m = 0; m < LETTERS; m++)
                    {
                        char *x = malloc(sizeof(char));
                        sprintf(x, "%c%c%c%c%c", convert(i), convert(j), convert(k), convert(l), convert(m));
                        bool result = test(x, salt, hash);
                        if (result)
                        {
                            printf("%s\n", x);
                            free(x);
                            free(salt);
                            return 0;
                        }
                        free(x);
                    }
                }
            }
        }
    }
    // free memory alloc'd
    free(salt);
}

char convert(int x)
{
    if (x < 26)
    {
        // uppercase first because they come before lowercase in ASCII table
        // A = 65, Z = 90
        char y = (char)(x + 65);
        return y;
    }
    else
    {
        // lowercase
        // a = 97, z = 122
        x = x % 26;
        char y = (char)(x + 97);
        return y;
    }
}

bool test(char *x, char *salt, char *hash)
{
    char *temp = crypt(x, salt);
    int result = strcmp(temp, hash);
    if (result == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
