#ifndef DATA_STRUCTURES_XOR_LINKED_LIST_H
#define DATA_STRUCTURES_XOR_LINKED_LIST_H

#include <data-structures.h>

typedef struct XorLinkedList * XorLinkedList;
typedef struct XorLinkedListNode * XorLinkedListNode;

DATA_STRUCTURES_API
XorLinkedList XorLinkedList_Create(
     DS_Size data_size
);

DATA_STRUCTURES_API
DS_Void XorLinkedList_Destroy(
     XorLinkedList xor_linked_list
);

DATA_STRUCTURES_API
DS_Generic XorLinkedListNode_GetData(
     XorLinkedListNode node
);

DATA_STRUCTURES_API
DS_Void XorLinkedList_PushHead(
     XorLinkedList    xor_linked_list,
     const DS_Generic data
);

DATA_STRUCTURES_API
DS_Void XorLinkedList_PushTail(
     XorLinkedList    xor_linked_list,
     const DS_Generic data
);

DATA_STRUCTURES_API
DS_Void XorLinkedList_PopHead(
     XorLinkedList xor_linked_list
);

DATA_STRUCTURES_API
DS_Void XorLinkedList_PopTail(
     XorLinkedList xor_linked_list
);

DATA_STRUCTURES_API
DS_Void XorLinkedList_Insert(
     XorLinkedList    xor_linked_list,
     DS_Size          index,
     const DS_Generic data
);

DATA_STRUCTURES_API
DS_Void XorLinkedList_Remove(
     XorLinkedList    xor_linked_list,
     const DS_Generic data
);

DATA_STRUCTURES_API
DS_Void XorLinkedList_Erase(
     XorLinkedList xor_linked_list,
     DS_Size       index
);

DATA_STRUCTURES_API
DS_Void XorLinkedList_Update(
     XorLinkedList    xor_linked_list,
     DS_Size          index,
     const DS_Generic data
);

#endif