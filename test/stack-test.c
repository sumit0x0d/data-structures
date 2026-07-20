#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <stack.h>


int main(void)
{
   Stack *stack;
   int i, value;

   srand((int)time(NULL));

   stack = Stack_Create(sizeof(int), 100);
   if (!stack) {
      fprintf(stderr, "Stack_Create() failed\n");
      return 1;
   }
   printf("Stack_Create() passed\n");

   for (i = 0; i < 10; i++) {
      value = rand() % 100;
      Stack_Push(stack, &value);
   }
   printf("Stack_Push() passed\n");
   Stack_Destroy(stack);
   printf("Stack_Destroy() passed\n");
   printf("All stack tests passed!\n");

   return 0;
}
