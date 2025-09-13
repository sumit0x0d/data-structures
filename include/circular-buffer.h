#ifndef DATA_STRUCTURES_CIRCULAR_BUFFER_H
#define DATA_STRUCTURES_CIRCULAR_BUFFER_H

#include <data-structures.h>

typedef struct circular_buffer * CircularBuffer;

DS_PUBLIC_API
CircularBuffer CircularBuffer_Create(DS_Size sData, DS_Size capacity);

DS_PUBLIC_API
void CircularBuffer_Destroy(CircularBuffer buffer);

DS_PUBLIC_API
DS_Bool CircularBuffer_IsEmpty(CircularBuffer buffer);

DS_PUBLIC_API
DS_Bool CircularBuffer_IsFull(CircularBuffer buffer);

DS_PUBLIC_API
DS_Data CircularBuffer_GetFrontData(CircularBuffer buffer);

DS_PUBLIC_API
DS_Data CircularBuffer_GetBackData(CircularBuffer buffer);

DS_PUBLIC_API
void CircularBuffer_PushBack(CircularBuffer buffer, const DS_Data data);

DS_PUBLIC_API
void CircularBuffer_PopFront(CircularBuffer buffer);

#endif
