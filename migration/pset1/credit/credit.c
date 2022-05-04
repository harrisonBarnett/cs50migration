#include <stdio.h>
#include <cs50.h>

int main(void)
{
    
    long number = 4003600000000014;
    
    int digit = number % 10;
    printf("%i\n", digit);
    
    number = number - 4;
    digit = number %10;
    printf("%i\n", digit);
    
}