#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    //Prompt user for a credit card number and check length for validity.

    long x = get_long("Credit Card Number: \n");
    if (x < 1000000000000 || x > 9999999999999999)
    {
        printf("INVALID\n");
        return 0;
    }
    //Now we have a 13, 15 or 16 digit credit card number

    //Isolate and double every other digit, starting from the second to last
    int y = 1, z = 1, pot = 0;
    for (int i = 0; i < 8; i++)
    {
        long a = x % (long)pow(10,2*y);
        long b = (long)pow(10,(2 * y - 1));
        long c = (a - (a % b)) / b;
        long d = 2 * c;
        if (d >= 10)
        {
            int r = d % 10;
            int o = (d - r) / 10;
            pot = pot + r + o;
        }
        else
        {
           pot = pot + d;
        }
        printf("cc digit: %li | pot: %i\n", c, pot);
        y++;
     }

    //Isolate every other digit starting with the last one, and add it to the pot

    for (int i = 0; i < 8; i++)
    {
        if (z == 1)
        {
            long d = x % 10;
            pot = pot + d;
            printf("cc digit: %li | pot: %i\n", d, pot);
        }
        else
        {
            long a = x % (long)pow(10,2 * z - 1);
            long b = (long)pow(10,(2 * z - 2));
            long d = (a - (a % b)) / b;
            pot = pot + d;
            printf("cc digit: %li | pot: %i\n", d, pot);
        }
        z++;
    }

        
    //Check sum % 10
    if (pot % 10 == 0)
    {
        int first = 0;
        //isolate the first two digits to check card type. Use int datatype to cut off decimals
        if (x > 999999999999 && x < 10000000000000) //13 digit
        {
            first = x / pow(10,11);
        }
        else if (x > 99999999999999 && x < 1000000000000000) //15 digit
        {
            first = x / pow(10,13);
        }
        else if (x > 999999999999999 && x < 10000000000000000) //16 digit
        {
            first = x / pow(10,14);
        }
        else
        {
            printf("INVALID\n"); //there are no 14 digit cards, exit the program if one got through the test.
             return 0;
        }

        if (first > 39 && first < 50)
        {
            printf("VISA\n");
             return 0;
        }
        else if (first == 34 || first == 37)
        {
            printf("AMEX\n");
             return 0;
        }
        else if (first > 50 && first < 56)
        {
            printf("MASTERCARD\n");
             return 0;
        }
        else
        {
            printf("INVALID\n");
             return 0;
        }
    }
    else
    {
        printf("INVALID\n");
         return 0;
    }
}
