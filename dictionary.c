/**
 * Implements a dictionary's functionality.
 */
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

/*data structure node
is_word ensures incomplete words are not determined to be "spelled correctly"
just because that sequence of characters exists in data structure in correct order.
array[27] is an array, each of whose index contains a pointer (to NULL or another node) */
typedef struct trie
{
    int is_word;
    struct trie* array[27];
} trie;

//keeps track of which index of array does not contain NULL pointer
int IndexNotNull;
//used for traversing nodes of data structure
trie* current = NULL;
trie* previous = NULL;
//root pointer
trie* root = NULL;

//marks the number of words loaded from dictionary file
int numwords = 0;
//stores character read from dictionary
char charReader;
//0 is false, 1 is true
int boolean;

/**
 * Returns true if word is in dictionary else false.
 */


//checks that all indices point to NULL
bool NullCheck(trie* node)
{
    for (int i = 0; i < 27; i++)
        {
        if (node->array[i] != NULL)
            {
            IndexNotNull = i;
            return false;
            }
        }
    return true;
}

//checks that all indices point to NULL
bool NullRootCheck(trie* node)
{
    for (int i = 0; i < 27; i++)
        {
        if (node->array[i] != NULL)
            {
            return false;
            }
        }
    return true;
}

//checks if each word in text file is found in dictionary
bool check(const char *word)
{

//assigns root pointer value to current pointer
current = root;
//stores character from string "word"
char character;
//corresponds to character's ordered array index
int index;

//for each word in text file, convert each letter to ascii value
for (int i = 0, j = strlen(word); i < j; i++)
    {
    character = word[i];
    if (isupper(character))
        index = (character - 65);
    else if (islower(character))
        index = (character - 97);
    else //(character == '\'')
        index = 26;

    /*array of node starts with all array pointers set to NULL
    as dictionary words are read, each letter is converted to ascii equivalent (similar to above example)
    for each letter, the array index of the corresponding ascii value points to a new trie node that is malloc'd
    the next section checks each letter's (from text file) associated ascii value against a trie node array index
    if pointer is NULL, letter does not exist in that node
    if pointer != NULL, "previous" pointer points to this node and "current" pointer advances to next node */
    if (current->array[index] == NULL)
        return false;
    else
        {
        previous = current;
        current = current->array[index];
        }
    }

/*ensures incomplete words are not determined to be "spelled correctly"
just because that sequence of characters exists in data structure in correct order. */
if (previous->is_word == 1)
    {
    current = NULL;
    previous = NULL;
    return true;
    }
else
    return false;

}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
//used for identifying specific index of trie array
int dex;

//root node from which all others will branch
root = malloc(sizeof(trie));
if (root == NULL)
    return false;
else
    {
    for (int k = 0; k < 27; k++)
        root->array[k] = NULL;
    }
//pointers that will be used for traversing nodes
trie* cur = NULL;
trie* prev = NULL;

//opens dictionary file for "read" access
FILE* DictPtr = fopen(dictionary, "r");
if (DictPtr == NULL)
    return false;
else
    //for each word of dictionary
    for (int i = 0; i < 143091; i++)
        {

        //sets current pointer to start at root pointer
        cur = root;

        //while character is letter or apostrophe, assigns ascii equivalent to int dex
        while ((isalpha(charReader = fgetc(DictPtr))) || (charReader == '\''))
            {
            if (charReader == '\'')
                {
                dex = 26;
                }
            else
                {
                dex = (charReader - 97);
                }

            /*if corresponding array index of trie node has pointer set to NULL,
            a new node is malloc'd (which will be used for next letter) and all array pointers set to NULL
            and index pointer points to new node*/
            if (cur->array[dex] == NULL)
                {
                trie* temp = malloc(sizeof(trie));
                    if (temp == NULL)
                        {
                        return false;
                        }
                    else
                        {
                        for (int j = 0; j < 27; j++)
                            {
                            temp->array[j] = NULL;
                            }
                        cur->array[dex] = temp;
                        }

                //previous pointer set to current node and current steps ahead to next node
                prev = cur;
                cur = cur->array[dex];
                }
            else if (cur->array[dex] != NULL)
                {
                cur = cur->array[dex];
                }
            }
        //marks node as being the end of a word contained in dictionary file
        prev->is_word = 1;
        numwords++;
        }
boolean = 1;
cur = NULL;
prev = NULL;

//closes FILE pointer after dictionary loaded into memory
fclose(DictPtr);
return true;

}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
//returns number of words loaded from dictionary (only if all words loaded)
if (boolean == 1)
    return numwords;
else
    return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    //starts current pointer at root node
    current = root;
    do
            {
            /*checks if all array indices of node point to NULL
            if so, current advances to next node */
            if (!NullCheck(current))
                {
                previous = current;
                current = current->array[IndexNotNull];
                }

            else
                /*we are at last node of chain
                index of previous node's array (that points to current node) is set to NULL
                current node is freed and current pointer starts back at root node */
                {
                previous->array[IndexNotNull] = NULL;
                free(current);
                current = root;
                }

        //while any pointer of root array is not NULL
        } while (!NullRootCheck(root));

current = NULL;
previous = NULL;
free(root);
root = NULL;
return true;

}

