#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <array.h>
#include <circular-buffer.h>

struct CircularBuffer {
     Array array;
     DS_Size front;
     DS_Size back;
     DS_Size size;
};

CircularBuffer CircularBuffer_Create(
     DS_Size data_size,
     DS_Size size
) {
     CircularBuffer circular_buffer;

     circular_buffer = (CircularBuffer)malloc(sizeof (struct CircularBuffer));
     if(!circular_buffer) {
          return NULL;
     }

     circular_buffer->array = Array_Create(data_size, size);
     if (!circular_buffer->array) {
          free(circular_buffer);
          return NULL;
     }

     circular_buffer->front = 0;
     circular_buffer->back = 0;

     return circular_buffer;
}

DS_Void CircularBuffer_Destroy(
     CircularBuffer circular_buffer
) {
     Array_Destroy(circular_buffer->array);
     free(circular_buffer);
}

DS_Bool CircularBuffer_IsEmpty(
     CircularBuffer circular_buffer
) {
     if (circular_buffer->size == 0) {
          return DS_TRUE;
     }
     
     return DS_FALSE;
}

DS_Bool CircularBuffer_IsFull(
     CircularBuffer circular_buffer
) {
     if (circular_buffer->size == Array_GetSize(
          circular_buffer->array)) {
          return DS_FALSE;
     }
     
     return DS_TRUE;
}

DS_Generic CircularBuffer_GetFrontData(
     CircularBuffer circular_buffer
) {
     return Array_GetData(circular_buffer->array, circular_buffer->front);
}

DS_Generic CircularBuffer_GetBackData(
     CircularBuffer circular_buffer
) {
     if (circular_buffer->back == 0) {
          return Array_GetData(circular_buffer->array,
               Array_GetSize(circular_buffer->array) - 1);
     } else {
          return Array_GetData(circular_buffer->array, circular_buffer->back - 1);
     }
     
     return NULL;
}

DS_Void CircularBuffer_PushBack(
     CircularBuffer   circular_buffer,
     const DS_Generic data
) {
     Array_SetData(circular_buffer->array, circular_buffer->back, data);
     circular_buffer->back = (circular_buffer->back + 1)
          % Array_GetSize(circular_buffer->array);
     circular_buffer->size++;
}

DS_Void CircularBuffer_PopFront(
     CircularBuffer circular_buffer
) {
     circular_buffer->front = (circular_buffer->front + 1)
          % Array_GetSize(circular_buffer->array);
     circular_buffer->size--;
}
