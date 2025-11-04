#ifndef DATA_STRUCTURES_CIRCULAR_BUFFER_H
#define DATA_STRUCTURES_CIRCULAR_BUFFER_H

#include <stdbool.h>

typedef struct CircularBuffer * CircularBuffer;

__attribute__((visibility("default")))
CircularBuffer CircularBuffer_Create(size_t data_size, size_t capacity);

__attribute__((visibility("default")))
void CircularBuffer_Destroy(CircularBuffer this);

__attribute__((visibility("default")))
bool CircularBuffer_IsEmpty(CircularBuffer this);

__attribute__((visibility("default")))
bool CircularBuffer_IsFull(CircularBuffer this);

__attribute__((visibility("default")))
void *CircularBuffer_GetFrontData(CircularBuffer this);

__attribute__((visibility("default")))
void *CircularBuffer_GetBackData(CircularBuffer this);

__attribute__((visibility("default")))
void CircularBuffer_PushBack(CircularBuffer this, const void *data);

__attribute__((visibility("default")))
void CircularBuffer_PopFront(CircularBuffer this);

#endif