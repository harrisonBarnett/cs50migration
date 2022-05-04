#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start;
    do 
    {
        start = get_int("Start? ");
    }
    while (start < 9);
    // TODO: Prompt for end size
    int end;
    do 
    {
        end = get_int("End? ");
    }
    while (end < start);

    // TODO: Calculate number of years until we reach threshold
    int years = 0;
    int population = start;
    while (population < end) 
    {
        int births = population / 3;
        int deaths = population / 4;
        population += (births - deaths);
        years++;
    }
    
    
    // TODO: Print number of years
    printf("Start size: %i\n", start);
    printf("End size: %i\n", end);
    printf("Years: %i\n", years);
}