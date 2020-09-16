#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //declare global int variable x
    int x = 0, h = 1;
    //prompt user for input between 1 and 8
    do
    {
    x = get_int("Input height: ");    
    }
    while(x < 1 || x > 8);
    
    //run loop x times for height of pyramid
    for (int i = 0; i < x; i++)
    {
        //print first spaces
        //each time we get to this for loop, x must be less by one because the number of spaces decreases by one
        //as the number of hashes increases by one
        //so set h equal to the number of hashes, it increases by one on each line
        for (int ia = 0; ia < x - h; ia++)
        {
            printf(" ");
        }
        //print first hashes
        //h is equal to one becuase we'll always have at least one
        for (int ib = 0; ib < h; ib++)
        {
            printf("#");
        }
        //print two spaces
        for (int ic = 0; ic < 2; ic++)
        {
            printf(" ");
        }
        //print last set of hashes, same amount as h before
        for (int id = 0; id < h; id++)
        {
            printf("#");
        }
        printf("\n");
        h++;
    }
    
}
