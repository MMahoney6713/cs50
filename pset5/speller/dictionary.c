// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

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


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Try opening the dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open dictionary\n");
        unload();
        return 1;
    }

    //for (int i = 0; i < N; i++)
    //{
    //    table[i]->next = NULL;
    //}


    // Hash each word in the dictionary into the hash table
    // Read each word in the dictionary using fscanf()
    char new_word[LENGTH + 1];
    //node *n = malloc(sizeof(node));

    while(fscanf(file, "%s", new_word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return 1;
        }
        n->next = NULL;

        // Link the new node to the last item in the linked list
        int hash_index = hash(new_word);
        //node *last_ptr = table[hash(new_word)];

        if (table[hash_index] == NULL)
        {
            table[hash_index] = n;
            strcpy(table[hash_index]->word, new_word);
        }
        else
        {
            node *last_ptr = table[hash_index];
            while (last_ptr->next != NULL)
            {
                last_ptr = last_ptr->next;
            }
            last_ptr->next = n;
            strcpy(last_ptr->next->word, new_word);
        }
    }
    fclose(file);
    return true;
}


// Hashes word to a number, using the lower case first letter of the word
unsigned int hash(const char *word)
{
    int send_to = ((int) tolower(word[0])) - 97;
    return send_to;
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // In order to find the size of the dictionary given the size of all of Table's
    // connections, must iterate through all of the linked items linked to Table

    int items_count = 0;
    node* next_ptr = NULL;
    for (int i = 0; i < N; i++)
    {
        next_ptr = table[i];
        // Go through each of the linked items down the ith bucket of table
        while (next_ptr != NULL)
        {
            items_count++;
            next_ptr = next_ptr->next;
        }
    }
    //printf("The number of words in the dictionary is %i\n", items_count);
    return items_count;
}


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node* next_ptr = table[hash(word)];
    while (next_ptr != NULL)
    {
        if (strcasecmp(word, next_ptr->word) == 0)
        // Word exists in dictionary
        {
            return true;
        }
        else
        {
            next_ptr = next_ptr->next;
        }
    }

    return false;
}


void free_linked_list(node* ptr)
{
    if (ptr == NULL)
    {
        return;
    }
    free_linked_list(ptr->next);
    free(ptr);
}


// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        free_linked_list(table[i]);
    }
    return true;
}

