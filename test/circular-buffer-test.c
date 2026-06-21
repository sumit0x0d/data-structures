#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <circular-buffer.h>

static void _UnaryPrint(void *data, void *user_data);

int main(void)
{
   CircularBuffer *obj;
   int i, value;
   CircularBufferUnaryCallback unary_callback;

   srand((int)time(NULL));
   unary_callback.function = _UnaryPrint;
   unary_callback.user_data = NULL;

   obj = CircularBuffer_Create(sizeof(int), 100);
   if (!obj) {
      fprintf(stderr, "CircularBuffer_Create() failed\n");
      return 1;
   }
   printf("CircularBuffer_Create() passed\n");

   for (i = 0; i < 10; i++) {
      value = rand() % 100;
      CircularBuffer_PushBack(cbuf, &value);
   }
   printf("CircularBuffer_Insert() passed\n");
   CircularBuffer_Traverse(cbuf, unary_callback);
   printf("\nCircularBuffer_Traverse() passed\n");
   CircularBuffer_Destroy(cbuf);
   printf("CircularBuffer_Destroy() passed\n");
   printf("All circular-buffer tests passed!\n");

   return 0;
}

static void _UnaryPrint(void *data, void *user_data)
{
   (void)user_data;
   printf("%d ", *(int *)data);
}
