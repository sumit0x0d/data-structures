#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <binary-search-tree.h>

typedef BinarySearchTreeNode Node;

struct BinarySearchTreeNode {
     DS_Generic data;
     BinarySearchTreeNode parent;
     BinarySearchTreeNode left;
     BinarySearchTreeNode right;
};

struct BinarySearchTree {
     BinarySearchTreeNode root;
     DS_Size data_size;
     DS_Size size;
     DS_CompareCallback compare_callback;
};

static BinarySearchTreeNode BinarySearchTreeNode_Create(const DS_Generic data, DS_Size size);
static DS_Void BinarySearchTreeNode_Destroy(BinarySearchTreeNode node);

BinarySearchTree BinarySearchTree_Create(DS_Size data_size, DS_CompareCallback compare_callback)
{
     BinarySearchTree self;
     self = (BinarySearchTree)malloc(sizeof (struct BinarySearchTree));
     assert(self);
     
     self->root = NULL;
     self->data_size = data_size;
     self->size = 0;
     self->compare_callback.function = compare_callback.function;
     self->compare_callback.user_data = compare_callback.user_data;
     
     return self;
}

DS_Void BinarySearchTree_Destroy(BinarySearchTree *self)
{
    free(self);
}

BinarySearchTreeNode BinarySearchTree_search(BinarySearchTree tree, const DS_Generic data)
{
     BinarySearchTreeNode node;

     node = tree->root;
     while (node) {
          switch (tree->compare_callback.function(node->data,
               data, tree->compare_callback.user_data)) {
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

DS_Void BinarySearchTree_insert(BinarySearchTree tree, const DS_Generic data)
{
     if (!tree->root) {
          tree->root = _BinarySearchTree_node_Create(
               data, tree->data_size);
          tree->root->parent = NULL;
          tree->size++;
          return;
     }
     BinarySearchTreeNode node = tree->root;
     BinarySearchTreeNode pnode = tree->root->parent;
     int compare = 0;
     while (node) {
          compare = tree->compare_callback.function(data,
               node->data, tree->compare_callback.user_data);
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
     node = _BinarySearchTree_node_Create(
          data, tree->data_size);
     node->parent = pnode;
     compare = tree->compare_callback.function(data,
          pnode->data, tree->compare_callback.user_data);
     if (compare < 0) {
          pnode->left = node;
     } else {
          pnode->right = node;
     }
     tree->size++;
}

DS_Void BinarySearchTree_remove(BinarySearchTree tree, const DS_Generic data)
{
     BinarySearchTreeNode node = tree->root;
     BinarySearchTreeNode pnode = tree->root->parent;
     while (node) {
          DS_Compare compare = tree->compare_callback.function(
               data, node->data, tree->compare_callback.user_data);
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
     (DS_Void)pnode;
}

static BinarySearchTreeNode _BinarySearchTreeNode_Create(const DS_Generic data, DS_Size size)
{
     BinarySearchTreeNode node = (BinarySearchTreeNode)malloc(sizeof (Node));
     assert(node);
     node->data = malloc(size);
     assert(node->data);
     memcpy(node->data, data, size);
     node->left = NULL;
     node->right = NULL;
     return node;
}

static DS_Void _BinarySearchTree_node_Destroy(BinarySearchTreeNode node)
{
     free(node->data);
     free(node);
}
