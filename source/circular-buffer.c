#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <array.h>
#include <circular-buffer.h>

struct circular_buffer {
     Array *array;
     size_t front;
     size_t back;
     size_t size;
};

CircularBuffer *CircularBuffer_Create(size_t dSize, size_t capacity)
{
     CircularBuffer *cBuffer = (CircularBuffer *)malloc(sizeof (CircularBuffer));
     assert(cBuffer);
     cBuffer->array = Array_Create(dSize, capacity);
     assert(cBuffer->array);
     cBuffer->front = 0;
     cBuffer->back = 0;
     return cBuffer;
}

void CircularBuffer_Destroy(CircularBuffer *cBuffer)
{
     Array_Destroy(cBuffer->array);
     free(cBuffer);
}

bool CircularBuffer_IsEmpty(CircularBuffer *cBuffer)
{
     if (cBuffer->size == 0) {
          return true;
     }
     return false;
}

bool CircularBuffer_IsFull(CircularBuffer *cBuffer)
{
     if (cBuffer->size == Array_GetSize(cBuffer->array)) {
          return true;
     }
     return false;
}

void *CircularBuffer_GetFrontData(CircularBuffer *cBuffer)
{
     return Array_GetData(cBuffer->array, cBuffer->front);
}

void *CircularBuffer_GetBackData(CircularBuffer *cBuffer)
{
     if (cBuffer->back == 0) {
          return Array_GetData(cBuffer->array, Array_GetSize(cBuffer->array) - 1);
     } else {
          return Array_GetData(cBuffer->array, cBuffer->back - 1);
     }
     return NULL;
}

void CircularBuffer_PushBack(CircularBuffer *cBuffer, const void *data)
{
     Array_SetData(cBuffer->array, cBuffer->back, data);
     cBuffer->size++;
     cBuffer->back = (cBuffer->back + 1) % Array_GetSize(cBuffer->array);
}

void CircularBuffer_PopFront(CircularBuffer *cBuffer)
{
     cBuffer->front = (cBuffer->front + 1) % Array_GetSize(cBuffer->array);
     cBuffer->size--;
}
