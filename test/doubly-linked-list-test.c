#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <doubly-linked-list.h>

static void _UnaryPrint(void *data, void *user_data);

int main(void)
{
   DoublyLinkedList *doubly_linked_list;
   int i, value;
   DoublyLinkedListUnaryCallback unary_callback;

   srand((int)time(NULL));
   unary_callback.function = _UnaryPrint;
   unary_callback.user_data = NULL;

   doubly_linked_list = DoublyLinkedList_Create(sizeof(int));
   if (!doubly_linked_list) {
      fprintf(stderr, "DoublyLinkedList_Create() failed\n");
      return 1;
   }
   printf("DoublyLinkedList_Create() passed\n");

   for (i = 0; i < 10; i++) {
      value = rand() % 100;
      DoublyLinkedList_PushFront(doubly_linked_list, &value);
   }
   printf("DoublyLinkedList_Insert() passed\n");
   DoublyLinkedList_Traverse(doubly_linked_list, unary_callback);
   printf("\nDoublyLinkedList_Traverse() passed\n");
   DoublyLinkedList_Destroy(doubly_linked_list);
   printf("DoublyLinkedList_Destroy() passed\n");
   printf("All doubly-linked-list tests passed!\n");

   return 0;
}

static void _UnaryPrint(void *data, void *user_data)
{
   (void)user_data;
   printf("%d ", *(int *)data);
}
