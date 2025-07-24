#include <assert.h>
#include <stdlib.h>

#include <array.h>
#include <stack.h>

struct stack {
     Array *array;
     size_t size;
};

Stack *Stack_Create(size_t dSize, size_t capacity)
{
     Stack *stack = (Stack *)malloc(sizeof (Stack));
     assert(stack);
     stack->array = Array_Create(dSize, capacity);
     assert(stack->array);
     stack->size = 0;
     return stack;
}

void Stack_Destroy(Stack *stack)
{
     Array_Destroy(stack->array);
     free(stack);
}

bool Stack_IsEmpty(Stack *stack)
{
     if (stack->size) {
          return false;
     }
     return true;
}

bool Stack_IsFull(Stack *stack)
{
     if (stack->size == Array_GetSize(stack->array)) {
          return true;
     }
     return false;
}

void *Stack_GetTop(Stack *stack)
{
     return Array_GetData(stack->array, stack->size - 1);
}

void Stack_Push(Stack *stack, const void *data)
{
     Array_SetData(stack->array, stack->size, data);
     stack->size++;
}

void Stack_Pop(Stack *stack)
{
     stack->size--;
}
