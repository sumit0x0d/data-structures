#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <binary-search-tree.h>

typedef BinarySearchTreeNode Node;

struct BinarySearchTree_node {
     DS_Data data;
     BinarySearchTreeNode parent;
     BinarySearchTreeNode left;
     BinarySearchTreeNode right;
};

struct binary_search_tree {
     BinarySearchTreeNode root;
     DS_Size data_size;
     DS_Size size;
     DS_FunctionCompare compare_function;
};

static BinarySearchTreeNode  BinarySearchTreeNode_Create(const DS_Data data, DS_Size size);
static void BinarySearchTreeNode_Destroy(BinarySearchTreeNode node);

BinarySearchTree BinarySearchTree_create(DS_Size sData, int (*compare)(const DS_Data data1, const DS_Data data2))
{
     BinarySearchTree tree = (BinarySearchTree *)malloc(sizeof (BinarySearchTree));
     assert(tree);
     tree->root = NULL;
     tree->data_size = sData;
     tree->size = 0;
     tree->compare_function = compare;
     return tree;
}

void BinarySearchTree_destroy(BinarySearchTree *tree)
{
     free(tree);
}

BinarySearchTreeNode BinarySearchTree_search(BinarySearchTree tree, const DS_Data data)
{
     BinarySearchTreeNode node = tree->root;
     while (node) {
          switch (tree->compare_function(node->data, data)) {
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

void BinarySearchTree_insert(BinarySearchTree *tree, const DS_Data data)
{
     if (!tree->root) {
          tree->root = _BinarySearchTree_node_create(data, tree->data_size);
          tree->root->parent = NULL;
          tree->size++;
          return;
     }
     BinarySearchTreeNode node = tree->root;
     BinarySearchTreeNode pnode = tree->root->parent;
     int compare = 0;
     while (node) {
          compare = tree->compare(data, node->data);
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
     node = _BinarySearchTree_node_create(data, tree->data_size);
     node->parent = pnode;
     compare = tree->compare(data, pnode->data);
     if (compare < 0) {
          pnode->left = node;
     } else {
          pnode->right = node;
     }
     tree->size++;
}

void BinarySearchTree_remove(BinarySearchTree *tree, const DS_Data data)
{
     BinarySearchTreeNode node = tree->root;
     BinarySearchTreeNode pnode = tree->root->parent;
     while (node) {
          int compare = tree->compare(data, node->data);
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

static BinarySearchTreeNode _BinarySearchTree_node_create(const DS_Data data, DS_Size size)
{
     BinarySearchTreeNode node = (BinarySearchTreeNode )malloc(sizeof (Node));
     assert(node);
     node->data = malloc(size);
     assert(node->data);
     memcpy(node->data, data, size);
     node->left = NULL;
     node->right = NULL;
     return node;
}

static void _BinarySearchTree_node_destroy(BinarySearchTreeNode node)
{
     free(node->data);
     free(node);
}
