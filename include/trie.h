#ifndef DATA_STRUCTURES_TRIE_H
#define DATA_STRUCTURES_TRIE_H



typedef struct Trie * Trie;
typedef struct TrieNode * TrieNode;

__attribute__((visibility("default")))
Trie Trie_Create(size_t data_size);

__attribute__((visibility("default")))
void Trie_Destroy(Trie this);

__attribute__((visibility("default")))
char *Trie_Search(Trie this, char *string);

__attribute__((visibility("default")))
DS_Bool Trie_Insert(Trie this, char *string);

__attribute__((visibility("default")))
int Trie_Remove(Trie this, char *string);

#endif