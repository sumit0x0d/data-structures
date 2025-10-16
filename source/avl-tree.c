#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <avl-tree.h>
#include <circular-buffer.h>
#include <stack.h>

#include "avl-tree-node.h"

// #include "binary-tree-i.h"

struct AvlTree {
     AvlTreeNode root;
     DS_Size data_size;
     DS_Size size;
     DS_CallbackCompare compare_callback;
     DS_Generic compare_context;
};

static DS_Void _Rebalance(
     AvlTree avl_tree,
     AvlTreeNode node,
     CircularBuffer circular_buffer
);
static DS_Void _RotateRight(
     AvlTree avl_tree,
     AvlTreeNode node
);
static DS_Void _RotateLeftRight(
     AvlTree avl_tree,
     AvlTreeNode node
);
static DS_Void _RotateLeft(
     AvlTree avl_tree,
     AvlTreeNode node
);
static DS_Void _RotateRightLeft(
     AvlTree avl_tree,
     AvlTreeNode node
);

AvlTree AvlTree_Create(
     DS_Size data_size,
     DS_CallbackCompare compare_callback,
     DS_Generic compare_context
) {
     AvlTree avl_tree;

     avl_tree = (AvlTree)malloc(sizeof (struct AvlTree));
     if (!avl_tree) {
          return NULL;
     }
     
     avl_tree->root = NULL;
     avl_tree->data_size = data_size;
     avl_tree->size = 0;
     avl_tree->compare_callback = compare_callback;
     avl_tree->compare_context = compare_context;
     
     return avl_tree;
}

DS_Void AvlTree_Destroy(
     AvlTree avl_tree
) {
     AvlTreeNode node ;
     CircularBuffer circular_buffer;

     node = avl_tree->root;
     circular_buffer = CircularBuffer_Create(sizeof (AvlTreeNode), avl_tree->size);
     
     free(node->data);
     CircularBuffer_PushBack(circular_buffer, node);
     
     while (!CircularBuffer_IsEmpty(circular_buffer)) {
          node = (AvlTreeNode)CircularBuffer_GetFrontData(circular_buffer);
          CircularBuffer_PopFront(circular_buffer);
          if (node->left) {
               free(node->data);
               CircularBuffer_PushBack(circular_buffer, node->left);
          }
          if (node->right) {
               free(node->data);
               CircularBuffer_PushBack(circular_buffer, node->right);
          }
     }
     
     CircularBuffer_Destroy(circular_buffer);
     free(avl_tree);
}

DS_Size AvlTree_GetSize(
     AvlTree avl_tree
) {
     return avl_tree->size;
}


DS_Size AvlTree_GetDataSize(
     AvlTree avl_tree
) {
     return avl_tree->data_size;
}


AvlTreeNode AvlTree_Search(
     AvlTree avl_tree,
     const DS_Generic data
) {
     AvlTreeNode current;
     DS_Compare compare;

     current = avl_tree->root;
     while (current) {
          compare = avl_tree->compare_callback(data,
               current->data, avl_tree->compare_context);
          switch (compare) {
          case DS_COMPARE_LESS:
               current = current->left;
               break;
          case DS_COMPARE_EQUAL:
               return current;
          case DS_COMPARE_GREATER:
               current = current->right;
               break;
          }
     }

     return NULL;
}

DS_Void AvlTree_Insert(
     AvlTree avl_tree,
     const DS_Generic data
) {
     CircularBuffer circular_buffer;
     AvlTreeNode current;
     AvlTreeNode parent;
     DS_Compare compare;

     if (!avl_tree->root) {
          avl_tree->root = AvlTreeNode_Create(data, avl_tree->data_size);
          avl_tree->root->parent = NULL;
          avl_tree->size++;
          return;
     }
     
     circular_buffer = CircularBuffer_Create(
          sizeof (struct AvlTreeNode),
          (avl_tree->size + 2) / 2);
     parent = avl_tree->root->parent;
          
     current = avl_tree->root;
     while (current) {
          compare = avl_tree->compare_callback(current->data,
               data, avl_tree->compare_context);
          if (compare == DS_COMPARE_EQUAL) {
               CircularBuffer_Destroy(circular_buffer);
               return;
          }
          parent = current;
          if (compare < DS_COMPARE_EQUAL) {
               current = current->left;
          } else {
               current = current->right;
          }
     }
     
     current = AvlTreeNode_Create(data, avl_tree->data_size);
     current->parent = parent;
     
     if (compare < 0) {
          parent->left = current;
     } else {
          parent->right = current;
     }

     _Rebalance(avl_tree, parent, circular_buffer);
     CircularBuffer_Destroy(circular_buffer);
     avl_tree->size++;
}

DS_Void AvlTree_Remove(
     AvlTree          avl_tree,
     const DS_Generic data
) {
     CircularBuffer circular_buffer;
     AvlTreeNode    current;
     AvlTreeNode    parent;
     DS_Compare     compare;

     circular_buffer = CircularBuffer_Create(
          sizeof (struct AvlTreeNode), (avl_tree->size + 2) / 2);
     parent = avl_tree->root->parent;
          
     current = avl_tree->root;
     while (current) {
          compare = avl_tree->compare_callback(data,
               current->data, avl_tree->compare_context);
          if (compare == 0) {
               break;
          }
          parent = current;
          if (compare < 0) {
               current = current->left;
          } else {
               current = current->right;
          }
     }
     
     if (!current) {
          return;
     }
     
     if (!current->left && !current->right) {
          if (parent->left == current) {
               parent->left = NULL;
          } else {
               parent->right = NULL;
          }
          AvlTreeNode_Destroy(current);
          _Rebalance(avl_tree, parent, circular_buffer);
     } else if (!current->left) {
          if (parent->right == current) {
               parent->right = current->right;
          } else {
               parent->left = current->right;
          }
          AvlTreeNode_Destroy(current);
          _Rebalance(avl_tree, parent, circular_buffer);
     } else if (!current->right) {
          if (parent->left == current) {
               parent->left = current->left;
          } else {
               parent->right = current->left;
          }
          AvlTreeNode_Destroy(current);
          _Rebalance(avl_tree, parent, circular_buffer);
     } else {
          if (avl_tree->root->balance_factor < 0) {
               current = AvlTreeNode_GetPredecessor(current);
          } else {
               current = AvlTreeNode_GetSuccessor(current);
          }
          _Rebalance(avl_tree, current, circular_buffer);
     }

     CircularBuffer_Destroy(circular_buffer);
     avl_tree->size--;
}

// DS_Void AvlTree_TraversePreorder(AvlTree avl_tree, DS_CallbackUnary unary_callback,
//     DS_Generic unary_context)
// {
// }

// DS_Void AvlTree_TraverseInorder(AvlTree avl_tree, DS_CallbackUnary unary_callback,
//     DS_Generic unary_context)
// {
// }

// DS_Void AvlTree_TraversePostorder(AvlTree avl_tree, DS_CallbackUnary unary_callback,
//     DS_Generic unary_context)
// {
// }

// DS_Void AvlTree_TraverseLevelorder(AvlTree avl_tree, DS_CallbackUnary unary_callback,
//     DS_Generic unary_context)
// {
// }


static DS_Void _RotateRight(
     AvlTree     avl_tree,
     AvlTreeNode node
) {
     AvlTreeNode left;

     left = node->left;

     node->left = left->right;
     if (node->left) {
          node->left->parent = node;
     }

     left->parent = node->parent;
     if (left->parent) {
          if (left->parent->left == node) {
               left->parent->left = left;
          } else {
               left->parent->right = left;
          }
     } else {
          avl_tree->root = left;
     }

     node->parent = left;
     left->right = node;
}

static DS_Void _RotateLeftRight(
     AvlTree     avl_tree,
     AvlTreeNode node
) {
     AvlTreeNode left;
     AvlTreeNode left_right;

     left = node->left;
     left_right = node->left->right;

     left->right = left_right->left;
     if (left->right) {
          left->right->parent = left;
     }

     node->left = left_right->right;
     if (node->left) {
          node->left->parent = node;
     }
     
     left_right->left = left;
     left->parent = left_right;

     left_right->parent = node->parent;
     if (left_right->parent) {
          if (left_right->parent->left == node) {
               left_right->parent->left = left_right;
          } else {
               left_right->parent->right = left_right;
          }
     } else {
          avl_tree->root = left_right;
     }

     node->parent = left_right;
     left_right->right = node;
}

static DS_Void _RotateLeft(
     AvlTree     avl_tree,
     AvlTreeNode node
) {
     AvlTreeNode right;

     right = node->right;
     
     node->right = right->left;
     if (node->right) {
          node->right->parent = node;
     }
     
     right->parent = node->parent;
     if (right->parent) {
          if (right->parent->left == node) {
               right->parent->left = right;
          } else {
               right->parent->right = right;
          }
     } else {
          avl_tree->root = right;
     }

     node->parent = right;
     right->left = node;
}

static DS_Void _RotateRightLeft(
     AvlTree     avl_tree,
     AvlTreeNode node
) {
     AvlTreeNode right;
     AvlTreeNode right_left;

     right = node->right;
     right_left = node->right->left;
     
     right->left = right_left->right;
     if (right->left) {
          right->left->parent = right;
     }

     node->right = right_left->left;
     if (node->right) {
          node->right->parent = node;
     }
     
     right_left->right = right;
     right->parent = right_left;

     right_left->parent = node->parent;
     if (right_left->parent) {
          if (right_left->parent->left == node) {
               right_left->parent->left = right_left;
          } else {
               right_left->parent->right = right_left;
          }
     } else {
          avl_tree->root = right_left;
     }
     
     node->parent = right_left;
     right_left->left = node;
}

static DS_Void _Rebalance(
     AvlTree        avl_tree,
     AvlTreeNode    node,
     CircularBuffer circular_buffer
) {
     while (node) {
          AvlTreeNode_UpdateBalanceFactor(node, circular_buffer);
          if (node->balance_factor == -2) {
               if (node->left->balance_factor == -1) {
                    _RotateRight(avl_tree, node);
                    AvlTreeNode_UpdateBalanceFactor(node, circular_buffer);
                    AvlTreeNode_UpdateBalanceFactor(node->right, circular_buffer);
               } else if (node->left->balance_factor == 1) {
                    _RotateLeftRight(avl_tree, node);
                    AvlTreeNode_UpdateBalanceFactor(node, circular_buffer);
               }
          } else if (node->balance_factor == 2) {
               if (node->right->balance_factor == 1) {
                    _RotateLeft(avl_tree, node);
                    AvlTreeNode_UpdateBalanceFactor(node, circular_buffer);
                    AvlTreeNode_UpdateBalanceFactor(node->left, circular_buffer);
               } else if (node->right->balance_factor == -1) {
                    _RotateRightLeft(avl_tree, node);
                    AvlTreeNode_UpdateBalanceFactor(node, circular_buffer);
               }
          }
          node = node->parent;
     }
}
