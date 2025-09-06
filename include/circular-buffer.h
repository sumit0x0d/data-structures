#ifndef DATA_STRUCTURES_CIRCULAR_BUFFER_H
#define DATA_STRUCTURES_CIRCULAR_BUFFER_H

#include <stddef.h>
#include <stdbool.h>

typedef struct circular_buffer CircularBuffer;

DS_PUBLIC_API
CircularBuffer *DS_CircularBuffer_Create(DS_Size size, DS_Size capacity);

DS_PUBLIC_API
void DS_CircularBuffer_Destroy(CircularBuffer *cBuffer);

DS_PUBLIC_API
bool DS_CircularBuffer_IsEmpty(CircularBuffer *cBuffer);

DS_PUBLIC_API
bool DS_CircularBuffer_IsFull(CircularBuffer *cBuffer);

DS_PUBLIC_API
void *DS_CircularBuffer_GetFrontData(CircularBuffer *cBuffer);

DS_PUBLIC_API
void *DS_CircularBuffer_GetBackData(CircularBuffer *cBuffer);

DS_PUBLIC_API
void DS_CircularBuffer_PushBack(CircularBuffer *cBuffer, const DS_Data data);

DS_PUBLIC_API
void DS_CircularBuffer_PopFront(CircularBuffer *cBuffer);

#endif
