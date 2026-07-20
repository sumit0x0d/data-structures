#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <singly-linked-list.h>

static void _UnaryPrint(void *data, void *user_data);

int main(void)
{
   SinglyLinkedList *singly_linked_list;
   int i, value;
   SinglyLinkedListUnaryCallback unary_callback;

   srand((int)time(NULL));
   unary_callback.function = _UnaryPrint;
   unary_callback.user_data = NULL;

   singly_linked_list = SinglyLinkedList_Create(sizeof(int));
   if (!singly_linked_list) {
      fprintf(stderr, "SinglyLinkedList_Create() failed\n");
      return 1;
   }
   printf("SinglyLinkedList_Create() passed\n");

   for (i = 0; i < 10; i++) {
      value = rand() % 100;
      SinglyLinkedList_PushFront(singly_linked_list, &value);
   }
   printf("SinglyLinkedList_Insert() passed\n");
   SinglyLinkedList_Traverse(singly_linked_list, unary_callback);
   printf("\nSinglyLinkedList_Traverse() passed\n");
   SinglyLinkedList_Destroy(singly_linked_list);
   printf("SinglyLinkedList_Destroy() passed\n");
   printf("All singly-linked-list tests passed!\n");

   return 0;
}

static void _UnaryPrint(void *data, void *user_data)
{
   (void)user_data;
   printf("%d ", *(int *)data);
}
