#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <array.h>
#include <circular-buffer.h>

struct circular_buffer {
     Array *array;
     DS_Size front;
     DS_Size back;
     DS_Size size;
};

CircularBuffer *DS_CircularBuffer_Create(DS_Size size, DS_Size capacity)
{
     CircularBuffer *cBuffer = (CircularBuffer *)malloc(sizeof (CircularBuffer));
     assert(cBuffer);
     cBuffer->array = DS_Array_Create(size, capacity);
     assert(cBuffer->array);
     cBuffer->front = 0;
     cBuffer->back = 0;
     return cBuffer;
}

void DS_CircularBuffer_Destroy(CircularBuffer *cBuffer)
{
     DS_Array_Destroy(cBuffer->array);
     free(cBuffer);
}

bool DS_CircularBuffer_IsEmpty(CircularBuffer *cBuffer)
{
     if (cBuffer->size == 0) {
          return true;
     }
     return false;
}

bool DS_CircularBuffer_IsFull(CircularBuffer *cBuffer)
{
     if (cBuffer->size == DS_Array_GetSize(cBuffer->array)) {
          return true;
     }
     return false;
}

void *DS_CircularBuffer_GetFrontData(CircularBuffer *cBuffer)
{
     return DS_Array_GetData(cBuffer->array, cBuffer->front);
}

void *DS_CircularBuffer_GetBackData(CircularBuffer *cBuffer)
{
     if (cBuffer->back == 0) {
          return DS_Array_GetData(cBuffer->array, DS_Array_GetSize(cBuffer->array) - 1);
     } else {
          return DS_Array_GetData(cBuffer->array, cBuffer->back - 1);
     }
     return NULL;
}

void DS_CircularBuffer_PushBack(CircularBuffer *cBuffer, const DS_Data data)
{
     DS_Array_SetData(cBuffer->array, cBuffer->back, data);
     cBuffer->size++;
     cBuffer->back = (cBuffer->back + 1) % DS_Array_GetSize(cBuffer->array);
}

void DS_CircularBuffer_PopFront(CircularBuffer *cBuffer)
{
     cBuffer->front = (cBuffer->front + 1) % DS_Array_GetSize(cBuffer->array);
     cBuffer->size--;
}
