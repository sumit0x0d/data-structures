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
     DS_Size  size;
};

static TrieNode *_TrieNode_Create();
// static DS_Void _TrieNode_Destroy();

Trie *node_Create(DS_Void)
{
     return NULL;
}

Trie *Trie_Create(DS_Void)
{
     Trie trie = (Trie *)malloc(sizeof (struct Trie));
     assert(trie);
     trie->root = NULL;
     trie->size = 0;
     return trie;
}

DS_Void Trie_Destroy(Trie *trie)
{
     free(trie);
}

// Node* search(Trie *T, char* string)
// {
//     Node* node = T->root;
//     return node;
// }

bool Trie_Insert(Trie *trie, char* string)
{
     if (!trie->root) {
          trie->root = _TrieNode_Create();
          if (!trie->root) {
               return false;
          }
     }
     Node *node = trie->root; 
     while (*string != '\0') {
          if (node->children[(DS_Size)*string] == NULL) {
               node->children[(DS_Size)*string] = _TrieNode_Create();
          }
          node = node->children[(DS_Size)*string];
          string++;
     }
     // DS_Size length = strlen(string);
     // for (DS_Size i = 0; i < length; i++) {
     //     if (node->children[(int)string[i]] == 0)
     //         node->children[(DS_Size)string[i]] = node_Create(string[i]);
     // }
     if (node->terminal) {
          return false;
     } else {
          node->terminal = 1;
     }
     trie->size = trie->size + 1;
     return true;
}

// DS_Void
// node_Destroy(Trie *T, char character)
// {
//     Node* node = T->root;
//     free(node);
// }

static Node *_TrieNode_Create()
{
     Node *node = (Node *)malloc(sizeof (Node));
     assert(node);
     node->terminal = 0;
     for (int i = 0; i < 128; i++) {
          node->children[i] = NULL;
     }
     // memset(node->children, '\0', sizeof (Node) * 128);
     return node;
}
