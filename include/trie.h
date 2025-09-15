#ifndef DATA_STRUCTURES_TRIE_H
#define DATA_STRUCTURES_TRIE_H

#include <data-structures.h>

typedef struct trie Trie;
typedef struct trie_node TrieNode;

DS_API
Trie *Trie_Create();

DS_API
void Trie_Destroy(Trie *trie);

DS_API
char *Trie_Search(Trie *trie, char *string);

DS_API
DS_Bool Trie_Insert(Trie *trie, char *string);

DS_API
int Trie_Remove(Trie *trie, char *string);

#endif
