#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <xor-linked-list.h>

static void _UnaryPrint(void *data, void *user_data);

int main(void)
{
   XorLinkedList *obj;
   int i, value;
   XorLinkedListUnaryCallback unary_callback;

   srand((int)time(NULL));
   unary_callback.function = _UnaryPrint;
   unary_callback.user_data = NULL;

   obj = XorLinkedList_Create(sizeof(int));
   if (!obj) {
      fprintf(stderr, "XorLinkedList_Create() failed\n");
      return 1;
   }
   printf("XorLinkedList_Create() passed\n");

   for (i = 0; i < 10; i++) {
      value = rand() % 100;
      XorLinkedList_PushFront(xor_list, &value);
   }
   printf("XorLinkedList_Insert() passed\n");
   XorLinkedList_Traverse(xor_list, unary_callback);
   printf("\nXorLinkedList_Traverse() passed\n");
   XorLinkedList_Destroy(xor_list);
   printf("XorLinkedList_Destroy() passed\n");
   printf("All xor-linked-list tests passed!\n");

   return 0;
}

static void _UnaryPrint(void *data, void *user_data)
{
   (void)user_data;
   printf("%d ", *(int *)data);
}
