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

CircularBuffer CircularBuffer_Create(DS_Size data_size, DS_Size size)
{
     CircularBuffer buffer = (CircularBuffer)malloc(sizeof (struct circular_buffer));
     assert(buffer);
     buffer->array = Array_Create(data_size, size);
     assert(buffer->array);
     buffer->front = 0;
     buffer->back = 0;
     return buffer;
}

DS_Void CircularBuffer_Destroy(CircularBuffer buffer)
{
     Array_Destroy(buffer->array);
     free(buffer);
}

DS_Bool CircularBuffer_IsEmpty(CircularBuffer buffer)
{
     if (buffer->size == 0) {
          return DS_TRUE;
     }
     return DS_FALSE;
}

DS_Bool CircularBuffer_IsFull(CircularBuffer buffer)
{
     if (buffer->size == Array_GetSize(buffer->array)) {
          return DS_FALSE;
     }
     return DS_TRUE;
}

DS_Data CircularBuffer_GetFrontData(CircularBuffer buffer)
{
     return Array_GetData(buffer->array, buffer->front);
}

DS_Data CircularBuffer_GetBackData(CircularBuffer buffer)
{
     if (buffer->back == 0) {
          return Array_GetData(buffer->array, Array_GetSize(buffer->array) - 1);
     } else {
          return Array_GetData(buffer->array, buffer->back - 1);
     }
     return NULL;
}

DS_Void CircularBuffer_PushBack(CircularBuffer buffer, const DS_Data data)
{
     Array_SetData(buffer->array, buffer->back, data);
     buffer->size++;
     buffer->back = (buffer->back + 1) % Array_GetSize(buffer->array);
}

DS_Void CircularBuffer_PopFront(CircularBuffer buffer)
{
     buffer->front = (buffer->front + 1) % Array_GetSize(buffer->array);
     buffer->size--;
}
