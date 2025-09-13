#include <assert.h>
#include <stdlib.h>

#include <array.h>
#include <stack.h>

struct stack {
     Array *array;
     DS_Size size;
};

Stack *Stack_Create(DS_Size sData, DS_Size capacity)
{
     Stack *stack = (Stack *)malloc(sizeof (Stack));
     assert(stack);
     stack->array = Array_Create(sData, capacity);
     assert(stack->array);
     stack->size = 0;
     return stack;
}

void Stack_Destroy(Stack *stack)
{
     Array_Destroy(stack->array);
     free(stack);
}

DS_Bool Stack_IsEmpty(Stack *stack)
{
     if (stack->size) {
          return DS_TRUE;
     }
     return DS_FALSE;
}

DS_Bool Stack_IsFull(Stack *stack)
{
     if (stack->size == Array_GetSize(stack->array)) {
          return DS_TRUE;
     }
     return DS_FALSE;
}

DS_Data Stack_GetTop(Stack *stack)
{
     return Array_GetData(stack->array, stack->size - 1);
}

void Stack_Push(Stack *stack, const DS_Data data)
{
     Array_SetData(stack->array, stack->size, data);
     stack->size++;
}

void Stack_Pop(Stack *stack)
{
     stack->size--;
}
