#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <xor-linked-list.h>

static void _UnaryPrint(void *data, void *user_data);

int main(void)
{
   XorLinkedList *xor_linked_list;
   int i, value;

   srand((int)time(NULL));

   xor_linked_list = XorLinkedList_Create(sizeof(int));
   if (!xor_linked_list) {
      fprintf(stderr, "XorLinkedList_Create() failed\n");
      return 1;
   }
   printf("XorLinkedList_Create() passed\n");

   for (i = 0; i < 5; i++) {
      value = rand() % 100;
      XorLinkedList_PushHead(xor_linked_list, &value);
   }
   for (i = 0; i < 5; i++) {
      value = rand() % 100;
      XorLinkedList_PushTail(xor_linked_list, &value);
   }
   printf("XorLinkedList_PushHead/PushTail() passed\n");

   XorLinkedList_PopHead(xor_linked_list);
   XorLinkedList_PopTail(xor_linked_list);
   printf("XorLinkedList_PopHead/PopTail() passed\n");
   XorLinkedList_Destroy(xor_linked_list);
   printf("XorLinkedList_Destroy() passed\n");
   printf("All xor-linked-list tests passed!\n");

   return 0;
}

static void _UnaryPrint(void *data, void *user_data)
{
   (void)user_data;
   printf("%d ", *(int *)data);
}
