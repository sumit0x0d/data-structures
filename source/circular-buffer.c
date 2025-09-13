#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <array.h>
#include <circular-buffer.h>

struct circular_buffer {
     Array array;
     DS_Size front;
     DS_Size back;
     DS_Size size;
};

CircularBuffer CircularBuffer_Create(DS_Size sData, DS_Size capacity)
{
     CircularBuffer cBuffer = (CircularBuffer)malloc(sizeof (struct circular_buffer));
     assert(cBuffer);
     cBuffer->array = Array_Create(sData, capacity);
     assert(cBuffer->array);
     cBuffer->front = 0;
     cBuffer->back = 0;
     return cBuffer;
}

void CircularBuffer_Destroy(CircularBuffer cBuffer)
{
     Array_Destroy(cBuffer->array);
     free(cBuffer);
}

DS_Bool CircularBuffer_IsEmpty(CircularBuffer cBuffer)
{
     if (cBuffer->size == 0) {
          return DS_TRUE;
     }
     return DS_FALSE;
}

DS_Bool CircularBuffer_IsFull(CircularBuffer cBuffer)
{
     if (cBuffer->size == Array_GetSize(cBuffer->array)) {
          return DS_FALSE;
     }
     return DS_TRUE;
}

DS_Data CircularBuffer_GetFrontData(CircularBuffer cBuffer)
{
     return Array_GetData(cBuffer->array, cBuffer->front);
}

DS_Data CircularBuffer_GetBackData(CircularBuffer cBuffer)
{
     if (cBuffer->back == 0) {
          return Array_GetData(cBuffer->array, Array_GetSize(cBuffer->array) - 1);
     } else {
          return Array_GetData(cBuffer->array, cBuffer->back - 1);
     }
     return NULL;
}

void CircularBuffer_PushBack(CircularBuffer cBuffer, const DS_Data data)
{
     Array_SetData(cBuffer->array, cBuffer->back, data);
     cBuffer->size++;
     cBuffer->back = (cBuffer->back + 1) % Array_GetSize(cBuffer->array);
}

void CircularBuffer_PopFront(CircularBuffer cBuffer)
{
     cBuffer->front = (cBuffer->front + 1) % Array_GetSize(cBuffer->array);
     cBuffer->size--;
}
