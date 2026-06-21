#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <doubly-linked-list.h>

static void _UnaryPrint(void *data, void *user_data);

int main(void)
{
   DoublyLinkedList *obj;
   int i, value;
   DoublyLinkedListUnaryCallback unary_callback;

   srand((int)time(NULL));
   unary_callback.function = _UnaryPrint;
   unary_callback.user_data = NULL;

   obj = DoublyLinkedList_Create(sizeof(int));
   if (!obj) {
      fprintf(stderr, "DoublyLinkedList_Create() failed\n");
      return 1;
   }
   printf("DoublyLinkedList_Create() passed\n");

   for (i = 0; i < 10; i++) {
      value = rand() % 100;
      DoublyLinkedList_PushFront(list, &value);
   }
   printf("DoublyLinkedList_Insert() passed\n");
   DoublyLinkedList_Traverse(list, unary_callback);
   printf("\nDoublyLinkedList_Traverse() passed\n");
   DoublyLinkedList_Destroy(list);
   printf("DoublyLinkedList_Destroy() passed\n");
   printf("All doubly-linked-list tests passed!\n");

   return 0;
}

static void _UnaryPrint(void *data, void *user_data)
{
   (void)user_data;
   printf("%d ", *(int *)data);
}
