#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <doubly-linked-list.h>

int
main()
{
     srand((int)time(NULL));
     struct doubly_linked_list *dlList = DoublyLinkedList_Create(sizeof (int));
     printf("%zu", DoublyLinkedList_GetSize(dlList));
     return 0;
}
