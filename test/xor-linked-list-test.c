#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "xor-linked-list.h"

int
main()
{
     srand((int)time(NULL));
     XorLinkedList *xlList = XorLinkedList_Create(sizeof (int));
     XorLinkedList_Destroy(xlList);
     return 0;
}
