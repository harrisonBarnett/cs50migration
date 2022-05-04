// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// initialize variables
unsigned int words = 0;
bool is_loaded = false;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // as "word" is constant, copy it to new string
    char temp[strlen(word)];
    strcpy(temp, word);

    // convert all chars in temp to lowercase
    // this makes the function case-insensitive
    for (int i = 0; i < strlen(temp); i++)
    {
        temp[i] = tolower(temp[i]);
    }

    // hash "word" to find its index in table
    int temp_hash = hash(temp);

    // initialize new node equal to the word we are checking
    node *ptr = table[temp_hash];
    while (ptr != NULL)
    {
        // compare the two strings
        if (strcmp(ptr->word, temp) == 0)
        {
            return true;
        }
        // set the pointer to the next node in the linked list
        ptr = ptr->next;
    }


    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    // find the int value of the first char in a word
    // using toupper to make it case-insensitive
    // - 'A' to account for indexing
    int word_hash = toupper(word[0]) - 'A';
    // take  the  modulus of the hash for proper placement within table
    return word_hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // open file, set to read
    // check to make sure it is not NULL
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open file\n");
        return false;
    }
    // variable of type string to temporarily store each "entry" of the dictionary
    char entry[LENGTH + 1];
    // iterate thru the dictionary until EOF (end of file)
    // this loop alphabetically hashes each dictionary entry into table
    while (fscanf(file, "%s", entry) != EOF)
    {
        // initialize temporary node and allocate space
        node *temp = malloc(sizeof(node));
        // find alphabetical position within indices of table
        int index = hash(entry);

        // copy the dictionary "entry" into temp
        strcpy(temp->word, entry);
        // set temp's pointer to the currnet "head" of table[index]
        temp->next = table[index];
        // set temp as "head" of table[index]
        table[index] = temp;
        words++;
    }
    fclose(file);
    is_loaded = true;
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // return 0 as there are no dictionary entries in memory
    if (is_loaded == false)
    {
        return 0;
    }
    return words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // iterate thru indices of table
    for (int i = 0; i < N; i++)
    {
        // temp pointer j = the "head" of table[i]
        node *j = table[i];
        // traverse linked list laterally until j is NULL
        while (j != NULL)
        {
            // temp pointer k = j
            node *k = j;
            // j = the next node in linked list
            j = j->next;
            // free the memory of data passed from j to k
            free(k);
        }
    }
    return true;
}
