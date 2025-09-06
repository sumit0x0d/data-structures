#include <assert.h>
#include <stdlib.h>

#include <array.h>
#include <stack.h>

struct stack {
     Array *array;
     DS_Size size;
};

Stack *DS_Stack_Create(DS_Size sData, DS_Size capacity)
{
     Stack *stack = (Stack *)malloc(sizeof (Stack));
     assert(stack);
     stack->array = DS_Array_Create(sData, capacity);
     assert(stack->array);
     stack->size = 0;
     return stack;
}

void DS_Stack_Destroy(Stack *stack)
{
     DS_Array_Destroy(stack->array);
     free(stack);
}

bool DS_Stack_IsEmpty(Stack *stack)
{
     if (stack->size) {
          return false;
     }
     return true;
}

bool DS_Stack_IsFull(Stack *stack)
{
     if (stack->size == DS_Array_GetSize(stack->array)) {
          return true;
     }
     return false;
}

void *DS_Stack_GetTop(Stack *stack)
{
     return DS_Array_GetData(stack->array, stack->size - 1);
}

void DS_Stack_Push(Stack *stack, const DS_Data data)
{
     DS_Array_SetData(stack->array, stack->size, data);
     stack->size++;
}

void DS_Stack_Pop(Stack *stack)
{
     stack->size--;
}
