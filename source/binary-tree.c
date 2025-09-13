#include <assert.h>
#include <stdlib.h>

#include <binary-tree.h>

typedef BinaryTreeNode Node;

struct binary_tree_node {
     DS_Data data;
     Node *parent;
     Node *left;
     Node *right;
};

struct binary_tree {
     Node *root;
     DS_Size data_size;
     DS_Size size;
};

static Node * _binary_tree_node_create(const DS_Data data, DS_Size size);
static void _binary_tree_node_destroy(Node *node);

BinaryTree binary_tree_create(DS_Size size)
{
    BinaryTree btree = (BinaryTree)malloc(sizeof (struct binary_tree));
    assert(btree);
    btree->root = NULL;
    btree->data_size = size;
    btree->size = 0;
    return btree;
}

void binary_tree_destroy(BinaryTree btree)
{
    free(btree);
}

void binary_tree_insert_left(BinaryTree btree, Node *pnode, const DS_Data data)
{

}

void binary_tree_insert_right(BinaryTree btree, Node pnode, const DS_Data data)
{
     if (!btree->root) {
          Node *node = _binary_tree_node_create(data, btree->data_size);
          node->parent = NULL;
          btree->size++;
          return;
     }
     
}

