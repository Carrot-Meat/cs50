// Implements a dictionary's functionality, used by pre-provided driver function which is not included
// Loads dictionary into trie then determines if input stream of words has mispellings

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;
int WORD_COUNT = 0;

// Represents a trie
node *root;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = calloc(1, sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        // Initialize variables
        node *temp = root;
        int len = strlen(word);
        int letter;
        // Iterate over letters in word
        for (int i = 0; i < len; i++)
        {
            // Map alphabet + apostrophe to 0 through 26
            letter = word[i] - 97;
            if (letter < 0)
            {
                letter = 26;
            }
            // If node is NULL create array and move to next node
            if (temp->children[letter] == NULL)
            {
                temp->children[letter] = calloc(1, sizeof(node));
                temp = temp->children[letter];
            }
            else
            {
                temp = temp->children[letter];
            }
            // Switch is_word flag on last letter of word
            if (i == len - 1)
            {
                temp->is_word = true;
                WORD_COUNT++;
            }
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
    return WORD_COUNT;
    return 0;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Initialize variables
    node *temp = root;
    int len = strlen(word);
    int letter;
    // Iterate over letters in word
    for (int i = 0; i < len; i++)
    {
        // Map alphabet + apostrophe to 0 through 26
        letter = tolower(word[i]) - 97;
        if (letter < 0)
        {
            letter = 26;
        }
        // If node is NULL word is mispelled
        temp = temp->children[letter];
        if (temp == NULL)
        {
            return false;
        }
        // On last letter of input check if is_word is true
        if (i == len - 1 && temp->is_word == true)
        {
            return true;
        }
    }
    return false;
}

bool rec_unload(node *node)
{
    for (int i = 0; i < N; i++)
    {
        if (node->children[i] != NULL)
        {
            rec_unload(node->children[i]);
        }
    }
    free(node);
    return true;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    return rec_unload(root);
    return false;
}
