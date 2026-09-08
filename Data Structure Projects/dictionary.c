// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 143093;

// Hash table
node *table[N];
unsigned int word_count = 0;

// prototype
unsigned int hash(const char *word);

bool check(const char *word)
{
    unsigned int index = hash(word);
    node *cursor = table[index];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0) {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number

unsigned int hash(const char *word)
{
    unsigned long hash_value = 5381;
    int c;
    while ((c = tolower(*word++))) {
        hash_value = ((hash_value << 5) + hash_value) + c;
    }
    return hash_value % N;
}

// Loads dictionary into memory, returning true if successful, else false

bool load(const char *dictionary)
{
    FILE *source = fopen(dictionary, "r");
    if(source == NULL)
    {
        return false;
    }
    char buffer[LENGTH + 1];

    while (fscanf(source, "%s", buffer) != EOF)
     {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(source);
            return false;
        }
        strcpy(new_node->word, buffer);
        unsigned int index = hash(buffer);
        new_node->next = table[index];
        table[index] = new_node;
        word_count++;
    }
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++) {
        node *cursor = table[i];
        while (cursor != NULL) {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
