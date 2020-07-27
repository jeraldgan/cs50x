// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 65536;

// Number of words in dictionary
int dictionary_size = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Create a lower case word array
    char lower_case_word[LENGTH+1];

    int n=strlen(word);

    // Convert the word to lower case
    for(int i=0; i<=n; i++){
        lower_case_word[i] = tolower(word[i]);
    }

    // Get the bucket of the word
    node *bucket = table[hash(lower_case_word)];

    // Check if the word exist in the bucket
    while(bucket != NULL){
        if(strcasecmp(bucket->word, lower_case_word)==0)
        {
            return true;
        }
        else
        {
            bucket = bucket->next;
        }
    }
    return false;
}

// Hashes word to a number
// Reference from https://cs50.stackexchange.com/questions/37209/pset5-speller-hash-function
unsigned int hash(const char *word)
{
    unsigned int hash_value = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
         hash_value = (hash_value << 2) ^ word[i];
    }
    return hash_value % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dictionary_file = fopen(dictionary, "r");
    if(dictionary_file == NULL)
    {
        return false;
    }

    char word[LENGTH+2];

    while(fscanf(dictionary_file, "%s", word)!=EOF)
    {
        node *new_node = malloc(sizeof(node));

        if(new_node == NULL){
            unload();
            return false;
        }

        strcpy(new_node->word, word);

        unsigned int word_hash = hash(word);

        if(table[word_hash] != NULL)
        {
            new_node->next=table[word_hash];
            table[word_hash]=new_node;
            dictionary_size++;
        } else {
           table[word_hash] = new_node;
           new_node->next = NULL;
           dictionary_size++;
        }
    }

    fclose(dictionary_file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dictionary_size;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    node *current_bucket;
    node *next_bucket;
    for(int i=0; i<N; i++){
        current_bucket = table[i];
        while(current_bucket != NULL)
        {
            next_bucket = current_bucket -> next;
            free(current_bucket);
            current_bucket = next_bucket;
        }
    }
    return true;
}
