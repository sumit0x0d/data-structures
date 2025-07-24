#ifndef DATA_STRUCTURES_TRIE_H
#define DATA_STRUCTURES_TRIE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct trie Trie;
typedef struct trie_node TrieNode;

Trie *Trie_Create();
void Trie_Destroy(Trie *trie);

char *Trie_Search(Trie *trie, char *string);
bool Trie_Insert(Trie *trie, char *string);
int Trie_Remove(Trie *trie, char *string);

#endif
