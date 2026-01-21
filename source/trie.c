#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <trie.h>

struct TrieNode {
   int terminal;
   TrieNode *children[128];
};

struct Trie {
   TrieNode *root;
   size_t  size;
};

static TrieNode *_TrieNode_Create();
// static void _TrieNode_Destroy();

Trie *node_Create(void)
{
   return NULL;
}

Trie *Trie_Create(void)
{
   Trie *trie = (Trie *)malloc(sizeof (struct Trie));
   assert(trie);
   trie->root = NULL;
   trie->size = 0;
   return trie;
}

void Trie_Destroy(Trie *trie)
{
   free(trie);
}

// Node* search(Trie *T, char* string)
// {
//   Node* node = T->root;
//   return node;
// }

bool Trie_Insert(Trie *trie, char* string)
{
   if (!trie->root) {
      trie->root = _TrieNode_Create();
      if (!trie->root) {
         return false;
      }
   }
   TrieNode *node = trie->root; 
   while (*string != '\0') {
      if (node->children[(size_t)*string] == NULL) {
         node->children[(size_t)*string] = _TrieNode_Create();
      }
      node = node->children[(size_t)*string];
      string++;
   }
   // size_t length = strlen(string);
   // for (size_t i = 0; i < length; i++) {
   //   if (node->children[(int)string[i]] == 0)
   //       node->children[(size_t)string[i]] = node_Create(string[i]);
   // }
   if (node->terminal) {
      return false;
   } else {
      node->terminal = 1;
   }
   trie->size = trie->size + 1;
   return true;
}

// void
// node_Destroy(Trie *T, char character)
// {
//   Node* node = T->root;
//   free(node);
// }

static TrieNode *_TrieNode_Create()
{
   TrieNode *node = (TrieNode *)malloc(sizeof (TrieNode));
   assert(node);
   node->terminal = 0;
   for (int i = 0; i < 128; i++) {
      node->children[i] = NULL;
   }
   // memset(node->children, '\0', sizeof (Node) * 128);
   return node;
}
