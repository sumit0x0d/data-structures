#include <stdlib.h>
#include <string.h>

#include <red-black-tree.h>
#include <array.h>
#include <circular-buffer.h>

#include "red-black-tree-node.h"

struct RedBlackTree {
     RedBlackTreeNode   root;
     DS_Size            data_size;
     DS_Size            size;
     DS_CallbackCompare compare_callback;
     DS_Generic         compare_context;
};

static DS_Void _RotateRight(
     RedBlackTree     red_black_tree,
     RedBlackTreeNode node
);
static DS_Void _RotateLeftRight(
     RedBlackTree     red_black_tree,
     RedBlackTreeNode node
);
static DS_Void _RotateLeft(
     RedBlackTree     red_black_tree,
     RedBlackTreeNode node
);
static DS_Void _RotateRightLeft(
     RedBlackTree     red_black_tree,
     RedBlackTreeNode node
);
static DS_Void _Rebalance(
     RedBlackTree     red_black_tree,
     RedBlackTreeNode node
);

RedBlackTree RedBlackTree_Create(
     DS_Size            size,
     DS_CallbackCompare compare_callback,
     DS_Generic         compare_context
) {
     RedBlackTree red_black_tree = (RedBlackTree)malloc(sizeof (struct RedBlackTree));
     if (!red_black_tree) {
          return NULL;
     }
     red_black_tree->root = NULL;
     red_black_tree->data_size = size;
     red_black_tree->size = 0;
     red_black_tree->compare_callback = compare_callback;
     red_black_tree->compare_context = compare_context;
     return red_black_tree;
}

DS_Void RedBlackTree_Destroy(
     RedBlackTree red_black_tree
) {
     RedBlackTreeNode node = red_black_tree->root;
     CircularBuffer circular_buffer = CircularBuffer_Create(
          sizeof (struct RedBlackTreeNode), red_black_tree->size);
     free(node->data);
     CircularBuffer_PushBack(circular_buffer, node);
     while (!CircularBuffer_IsEmpty(circular_buffer)) {
          node = (RedBlackTreeNode)CircularBuffer_GetFrontData(circular_buffer);
          CircularBuffer_PopFront(circular_buffer);
          if (node->left) {
               RedBlackTreeNode_Destroy(node);
               // CircularBuffer_PushBack(circular_buffer, node->left);
          }
          if (node->right) {
               RedBlackTreeNode_Destroy(node);
               // CircularBuffer_PushBack(circular_buffer, node->right);
          }
     }
     CircularBuffer_Destroy(circular_buffer);
     free(red_black_tree);
}

DS_Size RedBlackTree_GetSize(
     RedBlackTree red_black_tree
) {
     return red_black_tree->size;
}

RedBlackTreeNode RedBlackTree_Search(
     RedBlackTree     red_black_tree,
     const DS_Generic data
) {
     RedBlackTreeNode node = red_black_tree->root;
     while (node) {
          DS_Compare compare = red_black_tree->compare_callback(data, node->data,
               red_black_tree->compare_context);
          if (compare == DS_COMPARE_EQUAL) {
               return node;
          } else if (compare == DS_COMPARE_LESS) {
               node = node->left;
          } else {
               node = node->right;
          }
     }
     return NULL;
}

DS_Void RedBlackTree_Insert(
     RedBlackTree     red_black_tree,
     const DS_Generic data
) {
     if (!red_black_tree->root) {
          red_black_tree->root = RedBlackTreeNode_Create(data,
               red_black_tree->data_size);
          red_black_tree->root->parent = NULL;
          red_black_tree->root->color = 1;
          red_black_tree->size++;
          return;
     }
     RedBlackTreeNode node = red_black_tree->root;
     RedBlackTreeNode parent = red_black_tree->root->parent;
     DS_Compare compare;
     while (node) {
          compare = red_black_tree->compare_callback(data, node->data,
               red_black_tree->compare_context);
          if (compare == 0) {
               return;
          }
          parent = node;
          if (compare < 0) {
               node = node->left;
          } else {
               node = node->right;
          }
     }
     node = RedBlackTreeNode_Create(data, red_black_tree->data_size);
     node->parent = parent;
     node->color = 0;
     compare = red_black_tree->compare_callback(data, parent->data,
          red_black_tree->compare_context);
     if (compare < 0) {
          parent->left = node;
     } else {
          parent->right = node;
     }
     _Rebalance(red_black_tree, parent);
     red_black_tree->size++;
}

// DS_Void red_black_tree_remove(RedBlackTree tree, int data)
// {
// }

static DS_Void _RotateRight(
     RedBlackTree     red_black_tree,
     RedBlackTreeNode node
) {
     RedBlackTreeNode left = node->left;
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
          red_black_tree->root = left;
     }
     node->parent = left;
     left->right = node;
}

static DS_Void _RotateLeftRight(
     RedBlackTree     red_black_tree,
     RedBlackTreeNode node
) {
     RedBlackTreeNode left = node->left;
     RedBlackTreeNode left_right = node->left->right;
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
          red_black_tree->root = left_right;
     }
     node->parent = left_right;
     left_right->right = node;
}

static DS_Void _RotateLeft(
     RedBlackTree     red_black_tree,
     RedBlackTreeNode node
) {
     RedBlackTreeNode right = node->right; 
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
          red_black_tree->root = right;
     }
     node->parent = right;
     right->left = node;
}

static DS_Void _RotateRightLeft(
     RedBlackTree     red_black_tree,
     RedBlackTreeNode node
) {
     RedBlackTreeNode right = node->right;
     RedBlackTreeNode right_left = node->right->left;
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
          red_black_tree->root = right_left;
     }
     node->parent = right_left;
     right_left->left = node;
}

static DS_Void _Rebalance(
     RedBlackTree     red_black_tree,
     RedBlackTreeNode node
) {
     while (node) {
          if (node->color == RED_BLACK_TREE_NODE_COLOR_RED) {
               if (node->parent->left == node) {
                    if (!node->parent->right || node->parent->right->color == 1) {
                         _RotateRight(red_black_tree, node);
                    } else if (node->parent->right || node->parent->right->color == 0) {
                    }
               }
          }
          if (node->parent->left == node) {
               if (node->color == 0 &&
                  (!node->parent->right || node->parent->right->color == 1)) {
               }
               if (node->color == 0 &&
                  (node->parent->right && node->parent->right->color == 0)) {
                    node->parent->color = 1;
               }
          } else {
               if (node->color == 0 &&
                  (!node->parent->left || node->parent->left->color == 1)) {
                    _RotateLeft(red_black_tree, node);
                    _RotateRightLeft(red_black_tree, node);
                    _RotateLeftRight(red_black_tree, node);
                    _RotateRight(red_black_tree, node);
               }
               if (node->color == 0 &&
                  (node->parent->left && node->parent->left->color == 0)) {
                    node->parent->color = 1;
               }
          }
          red_black_tree->root = node->parent;
     }
}
