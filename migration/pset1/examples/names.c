#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main (void) 
{
    string names[] = {"Bill", "Charlie", "Fred", "George", "Jenny", "Percy", "Ron"};
    
    for (int i = 0; i < 7; i ++) 
    {
        // string compare
        // returns 0 for a match, pos or neg for !match
        if (strcmp(names[i], "Ron") == 0)
        {
            printf("Found \n");
            return 0;
        }
    }
    printf("Not found \n");
    return 1;
}