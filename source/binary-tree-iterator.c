#include <binary-tree-iterator.h>
#include <stack.h>

DS_Void GenericBinaryTree_TraversePreorder(
     DS_Generic node,
     DS_Size node_size,
     DS_Size binary_tree_size,
     DS_Size data_offeset,
     DS_Size left_offset,
     DS_Size right_offset,
     DS_CallbackUnary unary_callback,
     DS_Generic unary_context
) {
     Stack stack = Stack_Create(node_size, binary_tree_size);
     while (node || !Stack_IsEmpty(stack)) {
          if (node) {
               DS_Generic data = *(DS_Generic *)((DS_Int8 *)node + data_offeset);
               unary_callback(data, unary_context);
               Stack_Push(stack, node);
               node = *(DS_Generic *)((DS_Int8 *)node + left_offset);
          } else {
               node = *(DS_Generic *)Stack_GetTop(stack);
               Stack_Pop(stack);
               node = *(DS_Generic *)((DS_Int8 *)node + right_offset);
          }
     }
     Stack_Destroy(stack);
}


DS_Void GenericBinaryTree_TraverseInorder(
     DS_Generic node,
     DS_Size node_size,
     DS_Size binary_tree_size,
     DS_Size data_offeset,
     DS_Size left_offset,
     DS_Size right_offset,
     DS_CallbackUnary unary_callback,
     DS_Generic unary_context
) {
     Stack stack = Stack_Create(node_size, binary_tree_size);
     while (node || !Stack_IsEmpty(stack)) {
          if (node) {
               Stack_Push(stack, node);
               node = node->left;
          } else {
               node = (struct avl_tree_node)Stack_GetTop(stack);
               Stack_Pop(stack);
               atTraverse(node->data, context);
               node = node->right;
          }
     }
     Stack_Destroy(stack);
}

DS_Void GenericBinaryTree_TraverseInorder(DS_Generic node, DS_Size node_size,
                                             DS_Size binary_tree_size,
                                             DS_Size data_offeset, DS_Size left_offset,
                                             DS_Size right_offset,
                                             DS_CallbackUnary unary_callback,
                                             DS_Generic unary_context)
{
     Node node = tree->root;
     Stack stack = Stack_Create(sizeof (struct avl_tree_node), tree->size);
     while (node || !Stack_IsEmpty(stack)) {
          if (node) {
               Stack_Push(stack, node);
               atTraverse(node->data, context);
               node = node->left;
          } else {
               node = (struct avl_tree_node)Stack_GetTop(stack);
               Stack_Pop(stack);
               node = node->right;
          }
     }
     Stack_Destroy(stack);
}

DS_Void GenericBinaryTree_TraverseLevelorder(DS_Generic node, DS_Size node_size,
                                             DS_Size binary_tree_size,
                                             DS_Size data_offeset, DS_Size left_offset,
                                             DS_Size right_offset,
                                             DS_CallbackUnary unary_callback,
                                             DS_Generic unary_context)
{
     Node node = tree->root;
     CircularBuffer *buffer = CircularBuffer_Create(sizeof (struct avl_tree_node), tree->size);
     atTraverse(node->data, context);
     CircularBuffer_PushBack(buffer, node);
     while (!CircularBuffer_IsEmpty(buffer)) {
          node = CircularBuffer_GetFrontData(buffer);
          CircularBuffer_PopFront(buffer);
          if (node->left) {
               atTraverse(node->data, context);
               CircularBuffer_PushBack(buffer, node->left);
          }
          if (node->right) {
               atTraverse(node->data, context);
               CircularBuffer_PushBack(buffer, node->right);
          }
     }
     CircularBuffer_Destroy(buffer);
}
