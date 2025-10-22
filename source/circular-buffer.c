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

CircularBuffer CircularBuffer_Create(DS_Size data_size, DS_Size size)
{
     CircularBuffer self;

     self = (CircularBuffer)malloc(sizeof (struct CircularBuffer));
     if(!self) {
          return NULL;
     }

     self->array = Array_Create(data_size, size);
     if (!self->array) {
          free(self);
          return NULL;
     }

     self->front = 0;
     self->back = 0;

     return self;
}

DS_Void CircularBuffer_Destroy(CircularBuffer self)
{
     Array_Destroy(self->array);
     free(self);
}

DS_Bool CircularBuffer_IsEmpty(CircularBuffer self)
{
     if (self->size == 0) {
          return DS_BOOL_TRUE;
     }
     
     return DS_BOOL_FALSE;
}

DS_Bool CircularBuffer_IsFull(CircularBuffer self)
{
     if (self->size == Array_GetSize(
          self->array)) {
          return DS_BOOL_FALSE;
     }
     
     return DS_BOOL_TRUE;
}

DS_Generic CircularBuffer_GetFrontData(CircularBuffer self)
{
     return Array_GetData(self->array, self->front);
}

DS_Generic CircularBuffer_GetBackData(CircularBuffer self)
{
     if (self->back == 0) {
          return Array_GetData(self->array, Array_GetSize(self->array) - 1);
     } else {
          return Array_GetData(self->array, self->back - 1);
     }
     
     return NULL;
}

DS_Void CircularBuffer_PushBack(CircularBuffer self, const DS_Generic data)
{
     Array_SetData(self->array, self->back, data);
     self->back = (self->back + 1) % Array_GetSize(self->array);
     self->size++;
}

DS_Void CircularBuffer_PopFront(CircularBuffer self)
{
     self->front = (self->front + 1) % Array_GetSize(self->array);
     self->size--;
}
