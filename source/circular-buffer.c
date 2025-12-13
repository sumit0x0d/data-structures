#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <circular-buffer.h>

struct CircularBuffer {
     void *base;
     size_t data_size;
     size_t front;
     size_t back;
     size_t capacity;
};

CircularBuffer *CircularBuffer_Create(size_t data_size, size_t capacity)
{
     CircularBuffer *this;

     this = (CircularBuffer *)malloc(sizeof (CircularBuffer));
     if(!this) {
          return NULL;
     }

     this->base = malloc(data_size * capacity);
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

void CircularBuffer_Destroy(CircularBuffer *this)
{
     free(this->base);
     free(this);
}

bool CircularBuffer_IsEmpty(const CircularBuffer *this)
{
     if (this->front == this->back) {
          return true;
     }

     return false;
}

bool CircularBuffer_IsFull(const CircularBuffer *this)
{
     if (this->front == (this->back + 1) % this->capacity) {
          return true;
     }

     return false;
}

void *CircularBuffer_GetFrontData(const CircularBuffer *this)
{
     return (char *)this->base + (this->data_size * this->front);
}

void *CircularBuffer_GetBackData(const CircularBuffer *this)
{
     size_t index;

     if (this->front == this->back) {
          return NULL;
     }

     index = (this->back == 0) ? (this->capacity - 1) : (this->back - 1);

     return (char *)this->base + (this->data_size * index);
}

void CircularBuffer_PushBack(CircularBuffer *this, const void *data)
{
     memcpy((char *)this->base + this->data_size * this->back, data, this->data_size);
     this->back = (this->back + 1) % this->capacity;
}

void CircularBuffer_PopFront(CircularBuffer *this)
{
     this->front = (this->front + 1) % this->capacity;
}
