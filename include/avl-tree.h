#ifndef DATA_STRUCTURES_AVL_TREE_H
#define DATA_STRUCTURES_AVL_TREE_H

#include <stddef.h>

typedef struct avl_tree_node AvlTreeNode;
typedef struct avl_tree AvlTree;
typedef int (*AvlTreeCompare)(const void *data1, const void *data2, void *uData);
typedef void (*AvlTreeTraverse)(void *data, void *uData);

AvlTree *AvlTree_Create(size_t dSize, AvlTreeCompare atCompare, void *uData);
void AvlTree_Destroy(AvlTree *aTree);

size_t AvlTree_GetSize(AvlTree *aTree);
size_t AvlTree_GetDataSize(AvlTree *aTree);
void *AvlTreeNode_GetData(AvlTreeNode *node);

AvlTreeNode *AvlTree_Search(AvlTree *aTree, const void *data);

void AvlTree_Insert(AvlTree *aTree, const void *data);
void AvlTree_Remove(AvlTree *aTree, const void *data);

void AvlTree_TraversePreorder(AvlTree *aTree, AvlTreeTraverse atTraverse, void *uData);
void AvlTree_TraverseInorder(AvlTree *aTree, AvlTreeTraverse atTraverse, void *uData);
void AvlTree_TraversePostorder(AvlTree *aTree, AvlTreeTraverse atTraverse, void *uData);
void AvlTree_TraverseLevelorder(AvlTree *aTree, AvlTreeTraverse atTraverse, void *uData);

#endif
