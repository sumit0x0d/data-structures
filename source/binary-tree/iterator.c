#include "iterator.h"
#include <stack.h>

void GenericBinaryTree_TraversePreorder(
     void *node,
     size_t node_size,
     size_t binary_tree_size,
     size_t data_offeset,
     size_t left_offset,
     size_t right_offset,
     DS_UnaryCallback unary_callback
) {
     Stack stack = Stack_Create(node_size, binary_tree_size);
     while (node || !Stack_IsEmpty(stack)) {
          if (node) {
               void *data = *(void **)((char *)node + data_offeset);
               unary_callback.function(data, unary_callback.user_data);
               Stack_Push(stack, node);
               node = *(void **)((char *)node + left_offset);
          } else {
               node = *(void **)Stack_GetTop(stack);
               Stack_Pop(stack);
               node = *(void **)((char *)node + right_offset);
          }
     }
     Stack_Destroy(stack);
}


void GenericBinaryTree_TraverseInorder(
     void *node,
     size_t node_size,
     size_t binary_tree_size,
     size_t data_offeset,
     size_t left_offset,
     size_t right_offset,
     DS_ unary_callback.function,
     void *unary_callback.user_data
) {
     Stack stack = Stack_Create(node_size, binary_tree_size);
     while (node || !Stack_IsEmpty(stack)) {
          if (node) {
               Stack_Push(stack, node);
               node = node->left;
          } else {
               node = (struct avl_tree_node)Stack_GetTop(stack);
               Stack_Pop(stack);
               atTraverse(node->data, user_data);
               node = node->right;
          }
     }
     Stack_Destroy(stack);
}

void GenericBinaryTree_TraverseInorder(void *node, size_t node_size,
                                             size_t binary_tree_size,
                                             size_t data_offeset, size_t left_offset,
                                             size_t right_offset,
                                             DS_CallbackUnary unary_callback.function,
                                             void *unary_callback.user_data)
{
     Node node = tree->root;
     Stack stack = Stack_Create(sizeof (struct avl_tree_node), tree->size);
     while (node || !Stack_IsEmpty(stack)) {
          if (node) {
               Stack_Push(stack, node);
               atTraverse(node->data, user_data);
               node = node->left;
          } else {
               node = (struct avl_tree_node)Stack_GetTop(stack);
               Stack_Pop(stack);
               node = node->right;
          }
     }
     Stack_Destroy(stack);
}

void GenericBinaryTree_TraverseLevelorder(void *node, size_t node_size,
                                             size_t binary_tree_size,
                                             size_t data_offeset, size_t left_offset,
                                             size_t right_offset,
                                             DS_CallbackUnary unary_callback.function,
                                             void *unary_callback.user_data)
{
     Node node = tree->root;
     CircularBuffer *buffer = CircularBuffer_Create(sizeof (struct avl_tree_node), tree->size);
     atTraverse(node->data, user_data);
     CircularBuffer_PushBack(buffer, node);
     while (!CircularBuffer_IsEmpty(buffer)) {
          node = CircularBuffer_GetFrontData(buffer);
          CircularBuffer_PopFront(buffer);
          if (node->left) {
               atTraverse(node->data, user_data);
               CircularBuffer_PushBack(buffer, node->left);
          }
          if (node->right) {
               atTraverse(node->data, user_data);
               CircularBuffer_PushBack(buffer, node->right);
          }
     }
     CircularBuffer_Destroy(buffer);
}
