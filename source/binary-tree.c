#include <assert.h>
#include <stdlib.h>

#include <binary-tree.h>

typedef BinaryTreeNode Node;

struct binary_tree_node {
     void *data;
     Node *parent;
     Node *left;
     Node *right;
};

struct binary_tree {
     Node *root;
     size_t data_size;
     size_t size;
};

static Node * _binary_tree_node_create(const void *data, size_t dsize);
static void _binary_tree_node_destroy(Node *node);

BinaryTree *binary_tree_create(size_t dsize)
{
    BinaryTree *btree = (BinaryTree *)malloc(sizeof (BinaryTree));
    assert(btree);
    btree->root = NULL;
    btree->data_size = dsize;
    btree->size = 0;
    return btree;
}

void binary_tree_destroy(BinaryTree *btree)
{
    free(btree);
}

void binary_tree_insert_left(BinaryTree *btree, Node *pnode, const void *data)
{

}

void binary_tree_insert_right(BinaryTree *btree, Node *pnode, const void *data)
{
     if (!btree->root) {
          Node *node = _binary_tree_node_create(data, btree->data_size);
          node->parent = NULL;
          btree->size++;
          return;
     }
     
}

