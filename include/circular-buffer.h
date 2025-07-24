#ifndef DATA_STRUCTURES_CIRCULAR_BUFFER_H
#define DATA_STRUCTURES_CIRCULAR_BUFFER_H

#include <stddef.h>
#include <stdbool.h>

typedef struct circular_buffer CircularBuffer;

CircularBuffer *CircularBuffer_Create(size_t dSize, size_t capacity);
void CircularBuffer_Destroy(CircularBuffer *cBuffer);

bool CircularBuffer_IsEmpty(CircularBuffer *cBuffer);
bool CircularBuffer_IsFull(CircularBuffer *cBuffer);

void *CircularBuffer_GetFrontData(CircularBuffer *cBuffer);
void *CircularBuffer_GetBackData(CircularBuffer *cBuffer);

void CircularBuffer_PushBack(CircularBuffer *cBuffer, const void *data);
void CircularBuffer_PopFront(CircularBuffer *cBuffer);

#endif
