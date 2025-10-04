#ifndef DATA_STRUCTURES_DOUBLY_LINKED_LIST_H
#define DATA_STRUCTURES_DOUBLY_LINKED_LIST_H

#include <data-structures.h>

typedef struct DoublyLinkedList * DoublyLinkedList;
typedef struct DoublyLinkedListNode * DoublyLinkedListNode;
typedef struct DoublyLinkedListIterator * DoublyLinkedListIterator;

DATA_STRUCTURES_API DoublyLinkedList
DoublyLinkedList_Create(DS_Size data_size);

DATA_STRUCTURES_API DS_Void
DoublyLinkedList_Destroy(DoublyLinkedList doubly_linked_list);

DATA_STRUCTURES_API DS_Size
DoublyLinkedList_GetSize(DoublyLinkedList doubly_linked_list);

DATA_STRUCTURES_API DS_Size
DoublyLinkedList_GetDataSize(DoublyLinkedList doubly_linked_list);

DATA_STRUCTURES_API DoublyLinkedListNode
DoublyLinkedList_GetHead(DoublyLinkedList doubly_linked_list);

DATA_STRUCTURES_API DoublyLinkedListNode
DoublyLinkedList_GetTail(DoublyLinkedList doubly_linked_list);

DATA_STRUCTURES_API DS_Generic
DoublyLinkedList_GetNodeData(DoublyLinkedListNode node);

DATA_STRUCTURES_API DS_Void
DoublyLinkedList_SetNodeData(DoublyLinkedList doubly_linked_list,
                             DoublyLinkedListNode node, const DS_Generic data);

DATA_STRUCTURES_API DS_Void
DoublyLinkedList_PushHead(DoublyLinkedList doubly_linked_list, const DS_Generic data);

DATA_STRUCTURES_API DS_Void
DoublyLinkedList_PushTail(DoublyLinkedList doubly_linked_list, const DS_Generic data);

DATA_STRUCTURES_API DS_Void
DoublyLinkedList_PopHead(DoublyLinkedList doubly_linked_list);

DATA_STRUCTURES_API DS_Void
DoublyLinkedList_PopTail(DoublyLinkedList doubly_linked_list);

DATA_STRUCTURES_API DS_Void
DoublyLinkedList_RemoveNode(DoublyLinkedList doubly_linked_list,
                            DoublyLinkedListNode node);

DATA_STRUCTURES_API DS_Void
DoublyLinkedList_Traverse(DoublyLinkedList doubly_linked_list,
                          DS_CallbackUnary unary_callback,
                          DS_Generic unary_context);

DATA_STRUCTURES_API DoublyLinkedListIterator
DoublyLinkedList_CreateItreator(DoublyLinkedList doubly_linked_list);

#endif
