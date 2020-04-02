// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <cs50.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }


    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];
    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        node *newNode = malloc(sizeof(node));
        if (newNode == NULL)
        {
            // unload();
            return false;
        }
        int index = hash(word);
        strcpy(newNode->word, word);
        if (hashtable[index] == NULL)
        {
            //if first node being added to this hash table, just point hashtable[index]->next to the new node, where newNode->word = dictionary word
            //ensure newNode->next points to NULL (as this will end up being the end of the chain)
            newNode->next = NULL;
            hashtable[index] = newNode;
        }
        else
        {
            //chain currently exists, two step process
            //1. point newNode->next to chain
            newNode->next = hashtable[index];
            //2. point hashtable to newNode
            hashtable[index] = newNode;
        }
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        if (hashtable[i] != NULL)
        {
            node *cursor = hashtable[i];
            while (cursor != NULL)
            {
                count++;
                cursor = cursor->next;
            }
        }
    }
    return count;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *cursor = hashtable[hash(word)];
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        else
        {
            (cursor = cursor->next);
        }
    }
    //return false if there is no match
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = hashtable[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}
