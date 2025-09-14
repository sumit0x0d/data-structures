#include <generic-binary-tree-traverse.h>
#include <stack.h>

void GenericBinaryTree_TraversePreorder(GenericBinaryTreeTraverseInfo *bttcInfo)
{
    DS_Generic node = bttcInfo->tree_root;
    Stack stack = Stack_Create(bttcInfo->node_size, bttcInfo->tree_size);
    while (node || !Stack_IsEmpty(stack)) {
        if (node) {
            DS_Data data = *(DS_Data *)((DS_Int8 *)node + bttcInfo->data_offest);
            atTraverse(data, bttcInfo->traverse_context);
            Stack_Push(stack, node);
            node = *(DS_Generic *)((DS_Int8 *)node + bttcInfo->left_offset);
        } else {
            node = *(DS_Generic *)Stack_GetTop(stack);
            Stack_Pop(stack);
            node = *(DS_Generic *)((DS_Int8 *)node + bttcInfo->right_offset);
        }
    }
    Stack_Destroy(stack);
}