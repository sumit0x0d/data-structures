#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <dynamic-array.h>

static void _UnaryPrint(void *data, void *user_data);

int main(void)
{
   DynamicArray *dynamic_array;
   int i, value;
   DynamicArrayUnaryCallback unary_callback;

   srand((int)time(NULL));
   unary_callback.function = _UnaryPrint;
   unary_callback.user_data = NULL;

   dynamic_array = DynamicArray_Create(sizeof(int), 100, 2.0);
   if (!dynamic_array) {
      fprintf(stderr, "DynamicArray_Create() failed\n");
      return 1;
   }
   printf("DynamicArray_Create() passed\n");

   for (i = 0; i < 10; i++) {
      value = rand() % 100;
      DynamicArray_PushBack(dynamic_array, &value);
   }
   printf("DynamicArray_Insert() passed\n");
   DynamicArray_Traverse(dynamic_array, unary_callback);
   printf("\nDynamicArray_Traverse() passed\n");
   DynamicArray_Destroy(dynamic_array);
   printf("DynamicArray_Destroy() passed\n");
   printf("All dynamic-array tests passed!\n");

   return 0;
}

static void _UnaryPrint(void *data, void *user_data)
{
   (void)user_data;
   printf("%d ", *(int *)data);
}
