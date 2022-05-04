#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{

    float change;
    do
    {
        change = get_float("Change owed: ");
    }
    while(change < 0); // prompting user for a positive number
    
    // convert float to int, rounding to the nearest penny
    int cents = round(change * 100);
    // initialize counter to keep track of the number of coins
    int counter = 0;
    while(cents > 0)
    {
        if(cents >= 25)
        {
            while(cents >= 25)
            {
                cents -= 25;
                counter++;
            }
        }
        else if(cents >= 10)
        {
            while(cents >= 10)
            {
                cents -=10;
                counter++;
            }
        }
        else if(cents >= 5)
        {
            while(cents >= 5)
            {
                cents -= 5;
                counter++;
            }
        }
        else if(cents >= 1)
        {
            while(cents >= 1)
            {
                cents -= 1;
                counter++;
            }
        }
    }
    
    printf("%i\n", counter);

}