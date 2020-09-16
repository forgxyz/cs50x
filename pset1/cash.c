#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    //prompt user for amount of change owed in format xx.xx
    float c = 0;
    do
    {
        c = get_float("How much change is owed? Input: ");        
    }
    while (c < 0);
    
    //convert float to int and total number of cents
    //declare coin variables
    int total = round(c * 100), q = 0, d = 0, n = 0, p = 0;
    
    //if there are greater than 25 cents, add one to q and subtract 25 from total
    while (total > 24)
    {
        total = total - 25;
        q++;
    }
    
    //run the same for each coin size
    while (total > 9)
    {
        total = total - 10;
        d++;
    }


    while (total > 4)
    {
        total = total - 5;
        d++;
    }

     while (total > 0)
    {
        total = total - 1;
        p++;
    }
   
    
    int coins = q + d + n + p;
    printf("%i\n", coins);
}
