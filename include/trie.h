#ifndef DATA_STRUCTURES_TRIE_H
#define DATA_STRUCTURES_TRIE_H

#include <data-structures.h>

typedef struct Trie * Trie;
typedef struct TrieNode * TrieNode;

DATA_STRUCTURES_API
Trie Trie_Create(DS_Size data_size);

DATA_STRUCTURES_API
DS_Void Trie_Destroy(Trie this);

DATA_STRUCTURES_API
char *Trie_Search(Trie this, char *string);

DATA_STRUCTURES_API
DS_Bool Trie_Insert(Trie this, char *string);

DATA_STRUCTURES_API
int Trie_Remove(Trie this, char *string);

#endif