#include <assert.h>
#include <stdlib.h>

#include <array.h>
#include <stack.h>

struct Stack {
     Array   array;
     DS_Size size;
};

Stack Stack_Create(
     DS_Size data_size,
     DS_Size size
) {
     Stack stack = (Stack)malloc(sizeof (struct Stack));
     assert(stack);
     stack->array = Array_Create(data_size, size);
     assert(stack->array);
     stack->size = 0;
     return stack;
}

DS_Void Stack_Destroy(
     Stack stack
) {
     Array_Destroy(stack->array);
     free(stack);
}

DS_Bool Stack_IsEmpty(
     Stack stack
) {
     if (stack->size) {
          return DS_TRUE;
     }
     return DS_FALSE;
}

DS_Bool Stack_IsFull(
     Stack stack
) {
     if (stack->size == Array_GetSize(stack->array)) {
          return DS_TRUE;
     }
     return DS_FALSE;
}

DS_Generic Stack_GetTop(
     Stack stack
) {
     return Array_GetData(stack->array, stack->size - 1);
}

DS_Void Stack_Push(
     Stack            stack,
     const DS_Generic data
) {
     Array_SetData(stack->array, stack->size, data);
     stack->size++;
}

DS_Void Stack_Pop(
     Stack stack
) {
     stack->size--;
}
