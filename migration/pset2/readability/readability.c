#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>



int main(void)
{
    string text = get_string("Text: ");
    // convert all chars in the text to upper
    for (int i = 0; i < strlen(text); i++)
    {
        text[i] = toupper(text[i]);
    }

    // set sum of letters in the text
    float letter_sum = 0;
    float words = 1;
    float sentences = 0;


    for (int i = 0; i < strlen(text); i++)
    {
        // iterate thru chars in text to update letter_sum
        if (text[i] >= 65 && text[i] <= 90)
        {
            letter_sum++;
        }
        // update number of words
        if (isspace(text[i]))
        {
            words++;
        }
        // update number of sentences
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentences++;
        }
    }

    // Coleman-Liau index
    float L = (letter_sum / words) * 100;
    float S = (sentences / words) * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}


