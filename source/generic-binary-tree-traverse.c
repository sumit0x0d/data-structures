#include <generic-binary-tree-traverse.h>
#include <stack.h>

void GenericBinaryTree_TraversePreorder(DS_Generic gNode, DS_Size sNode, DS_Size sTree, DS_Offset oData,
                                        DS_Offset oLeft, DS_Offset oRight, DS_FunctionUnary fUnary,
                                        DS_Context cUnary)
{
    DS_Generic node = gNode;
    Stack stack = Stack_Create(sNode, sTree);
    while (node || !Stack_IsEmpty(stack)) {
        if (node) {
            DS_Data data = *(DS_Data *)((DS_Int8 *)node + oData);
            fUnary(data, cUnary);
            Stack_Push(stack, node);
            node = *(DS_Generic *)((DS_Int8 *)node + oLeft);
        } else {
            node = *(DS_Generic *)Stack_GetTop(stack);
            Stack_Pop(stack);
            node = *(DS_Generic *)((DS_Int8 *)node + oRight);
        }
    }
    Stack_Destroy(stack);
}


void GenericBinaryTree_TraverseInorder(DS_Generic gNode, DS_Size sNode, DS_Size sTree, DS_Offset oData,
                                       DS_Offset oLeft, DS_Offset oRight, DS_FunctionUnary fUnary,
                                       DS_Context cUnary)
{
    Node node = tree->root;
    Stack *stack = Stack_Create(sizeof (struct avl_tree_node), tree->size);
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

void GenericBinaryTree_TraversePostorder(DS_Generic gNode, DS_Size sNode, DS_Size sTree, DS_Offset oData,
                                          DS_Offset oLeft, DS_Offset oRight, DS_FunctionUnary fUnary,
                                          DS_Context cUnary)
{
    Node node = tree->root;
    Stack *stack = Stack_Create(sizeof (struct avl_tree_node), tree->size);
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

void GenericBinaryTree_TraverseLevelorder(DS_Generic gNode, DS_Size sNode, DS_Size sTree, DS_Offset oData,
                                          DS_Offset oLeft, DS_Offset oRight, DS_FunctionUnary fUnary,
                                          DS_Context cUnary)
{
    Node node = tree->root;
    CircularBuffer *cBuffer = CircularBuffer_Create(sizeof (struct avl_tree_node), tree->size);
    atTraverse(node->data, context);
    CircularBuffer_PushBack(cBuffer, node);
    while (!CircularBuffer_IsEmpty(cBuffer)) {
        node = CircularBuffer_GetFrontData(cBuffer);
        CircularBuffer_PopFront(cBuffer);
        if (node->left) {
            atTraverse(node->data, context);
            CircularBuffer_PushBack(cBuffer, node->left);
        }
        if (node->right) {
            atTraverse(node->data, context);
            CircularBuffer_PushBack(cBuffer, node->right);
        }
    }
    CircularBuffer_Destroy(cBuffer);
}
