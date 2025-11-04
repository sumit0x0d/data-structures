#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <circular-buffer.h>

struct CircularBuffer {
     DS_Generic base;
     DS_Size data_size;
     DS_Size front;
     DS_Size back;
     DS_Size capacity;
};

CircularBuffer CircularBuffer_Create(DS_Size data_size, DS_Size capacity)
{
     CircularBuffer this;

     this = (CircularBuffer)malloc(sizeof (struct CircularBuffer));
     if(!this) {
          return NULL;
     }

     this->base = (DS_Generic)malloc(data_size * capacity);
     if (!this->base) {
          free(this);
          return NULL;
     };

     this->data_size = data_size;
     this->front = 0;
     this->back = 0;
     this->capacity = capacity;

     return this;
}

DS_Void CircularBuffer_Destroy(CircularBuffer this)
{
     free(this->base);
     free(this);
}

DS_Bool CircularBuffer_IsEmpty(CircularBuffer this)
{
     if (this->front == this->back) {
          return DS_BOOL_TRUE;
     }
     
     return DS_BOOL_FALSE;
}

DS_Bool CircularBuffer_IsFull(CircularBuffer this)
{
     if (this->front == (this->back + 1) % this->capacity) {
          return DS_BOOL_TRUE;
     }
     
     return DS_BOOL_FALSE;
}

DS_Generic CircularBuffer_GetFrontData(CircularBuffer this)
{
     return (DS_Int8 *)this->base + (this->data_size * this->front);
}

DS_Generic CircularBuffer_GetBackData(CircularBuffer this)
{
     DS_Size index;

     if (this->front == this->back) {
          return NULL;
     }

     index = (this->back == 0) ? (this->capacity - 1) : (this->back - 1);

     return (DS_Int8 *)this->base + (this->data_size * index);
}

DS_Void CircularBuffer_PushBack(CircularBuffer this, const DS_Generic data)
{
     memcpy((DS_Int8 *)this->base + this->data_size * this->back, data, this->data_size);
     this->back = (this->back + 1) % this->capacity;
}

DS_Void CircularBuffer_PopFront(CircularBuffer this)
{
     this->front = (this->front + 1) % this->capacity;
}