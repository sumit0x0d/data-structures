#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <binary-search-tree.h>

typedef BinarySearchTreeNode Node;

struct binary_search_tree_node {
     void *data;
     Node *parent;
     Node *left;
     Node *right;
};

struct binary_search_tree {
     Node *root;
     size_t data_size;
     size_t size;
     int (*compare)(const void *data1, const void *data2);
};

static Node * _binary_search_tree_node_create(const void *data, size_t dsize);
static void _binary_search_tree_node_destroy(Node *node);

BinarySearchTree *binary_search_tree_create(size_t dsize, int (*compare)(const void *data1, const void *data2))
{
     BinarySearchTree *binary_search_tree = (BinarySearchTree *)malloc(sizeof (BinarySearchTree));
     assert(binary_search_tree);
     binary_search_tree->root = NULL;
     binary_search_tree->data_size = dsize;
     binary_search_tree->size = 0;
     binary_search_tree->compare = compare;
     return binary_search_tree;
}

void binary_search_tree_destroy(BinarySearchTree *bstree)
{
     free(bstree);
}

Node *binary_search_tree_search(BinarySearchTree *bstree, const void *data)
{
     Node *node = bstree->root;
     while (node) {
          switch (bstree->compare(node->data, data)) {
          case -1:
               node = node->left;
               break;
          case 0:
               return node;
          case 1:
               node = node->right;
               break;
          }
     }
     return NULL;
}

void binary_search_tree_insert(BinarySearchTree *bstree, const void *data)
{
     if (!bstree->root) {
          bstree->root = _binary_search_tree_node_create(data, bstree->data_size);
          bstree->root->parent = NULL;
          bstree->size++;
          return;
     }
     Node *node = bstree->root;
     Node *pnode = bstree->root->parent;
     int compare = 0;
     while (node) {
          compare = bstree->compare(data, node->data);
          if (compare == 0) {
               return;
          }
          pnode = node;
          if (compare == -1) {
               node = node->left;
          } else {
               node = node->right;
          }
     }
     node = _binary_search_tree_node_create(data, bstree->data_size);
     node->parent = pnode;
     compare = bstree->compare(data, pnode->data);
     if (compare < 0) {
          pnode->left = node;
     } else {
          pnode->right = node;
     }
     bstree->size++;
}

void binary_search_tree_remove(BinarySearchTree *bstree, const void *data)
{
     Node *node = bstree->root;
     Node *pnode = bstree->root->parent;
     while (node) {
          int compare = bstree->compare(data, node->data);
          if (compare == 0) {
               break;
          }
          pnode = node;
          if (compare == -1) {
               node = node->left;
          } else {
               node = node->right;
          }
     }
     if (!node) {
          return;
     }
     if (node->parent->left == node) {

     }
     if (node->parent->right == node) {

     }
     node->parent->left = node->left;
     (void)pnode;
}

static Node *_binary_search_tree_node_create(const void *data, size_t dsize)
{
     Node *node = (Node *)malloc(sizeof (Node));
     assert(node);
     node->data = malloc(dsize);
     assert(node->data);
     memcpy(node->data, data, dsize);
     node->left = NULL;
     node->right = NULL;
     return node;
}

static void _binary_search_tree_node_destroy(Node *node)
{
     free(node->data);
     free(node);
}
