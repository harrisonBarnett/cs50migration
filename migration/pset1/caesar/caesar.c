#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

void asciiConverter(string input, int key);

int main(int argc, string argv[])
{

    // conditional checks user input for two commands (calling the program, entering key)
    // checks to make sure key is an integer
    if (argc == 2 && atoi(argv[1]) != 0)
    {
        int key = atoi(argv[1]);

        string plainText = get_string("plaintext: ");

        asciiConverter(plainText, key);

        printf("Usage: ./caesar key\n");
        return 0;
    }

    return 1;
}

void asciiConverter(string input, int key)
{
    int length = strlen(input);
    char newChars[length]; // initiate array to store the ciphertext

    // iterate through individual chars of the input
    for (int i = 0; i < length; i++)
    {
        // decrease ascii index by 65
        // set alpha index, increase by key
        // increase modified alpha index by 65 to set ascii index
        // add returned char to array to build cipher
        if (input[i] >= 'A' && input[i] <= 'Z')
        {
            int alphaIndex = input[i] - 65;
            int newCharIndex = (alphaIndex + key) % 26;
            int asciiIndex = newCharIndex + 65;
            newChars[i] = (char)asciiIndex;
        }
        // same as above, but decreasing ascii index value by 97
        else if (input[i] >= 'a' && input[i] <= 'z')
        {
            int alphaIndex = input[i] - 97;
            int newCharIndex = (alphaIndex + key) % 26;
            int asciiIndex = newCharIndex + 97;
            newChars[i] = (char)asciiIndex;
        }
        else
        {
            newChars[i] = input[i];
        }

    }
    printf("ciphertext: ");
    for (int j = 0; j < length; j++)
    {
        printf("%c", newChars[j]);
    }
    printf("\n");
}