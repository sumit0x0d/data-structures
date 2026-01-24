#ifndef DATA_STRUCTURES_CIRCULAR_BUFFER_H
#define DATA_STRUCTURES_CIRCULAR_BUFFER_H

#include <stddef.h>

typedef struct CircularBuffer CircularBuffer;

typedef enum {
   CIRCULAR_BUFFER_BOOL_FALSE = 0,
   CIRCULAR_BUFFER_BOOL_TRUE = 1
} CircularBufferBool;

__attribute__((visibility("default")))
CircularBuffer *CircularBuffer_Create(size_t data_size, size_t capacity);

__attribute__((visibility("default")))
void CircularBuffer_Destroy(CircularBuffer *this);

__attribute__((visibility("default")))
CircularBufferBool CircularBuffer_IsEmpty(const CircularBuffer *this);

__attribute__((visibility("default")))
CircularBufferBool CircularBuffer_IsFull(const CircularBuffer *this);

__attribute__((visibility("default")))
void *CircularBuffer_GetFrontData(const CircularBuffer *this);

__attribute__((visibility("default")))
void *CircularBuffer_GetBackData(const CircularBuffer *this);

__attribute__((visibility("default")))
void CircularBuffer_PushBack(CircularBuffer *this, const void *data);

__attribute__((visibility("default")))
void CircularBuffer_PopFront(CircularBuffer *this);

#endif
