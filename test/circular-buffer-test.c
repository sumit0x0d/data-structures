#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <circular-buffer.h>

int main(void)
{
   CircularBuffer *circular_buffer;
   int i, value;
   int *front_data;

   srand((int)time(NULL));

   circular_buffer = CircularBuffer_Create(sizeof(int), 100);
   if (!circular_buffer) {
      fprintf(stderr, "CircularBuffer_Create() failed\n");
      return 1;
   }
   printf("CircularBuffer_Create() passed\n");

   for (i = 0; i < 10; i++) {
      value = rand() % 100;
      CircularBuffer_PushBack(circular_buffer, &value);
   }
   printf("CircularBuffer_PushBack() passed\n");

   while (!CircularBuffer_IsEmpty(circular_buffer)) {
      front_data = CircularBuffer_GetFrontData(circular_buffer);
      printf("%d ", *front_data);
      CircularBuffer_PopFront(circular_buffer);
   }
   printf("\nCircularBuffer_PopFront() passed\n");
   CircularBuffer_Destroy(circular_buffer);
   printf("CircularBuffer_Destroy() passed\n");
   printf("All circular-buffer tests passed!\n");

   return 0;
}
