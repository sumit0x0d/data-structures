#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "linked-list.h"

int main()
{
     srand((int)time(NULL));
     LinkedList *lList = LinkedList_Create(sizeof (int));
     (void)lList;
     return 0;
}
