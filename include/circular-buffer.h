#ifndef DATA_STRUCTURES_CIRCULAR_BUFFER_H
#define DATA_STRUCTURES_CIRCULAR_BUFFER_H

#include <data-structures.h>

typedef struct CircularBuffer * CircularBuffer;

DATA_STRUCTURES_API
CircularBuffer CircularBuffer_Create(DS_Size data_size, DS_Size capacity);

DATA_STRUCTURES_API
DS_Void CircularBuffer_Destroy(CircularBuffer this);

DATA_STRUCTURES_API
DS_Bool CircularBuffer_IsEmpty(CircularBuffer this);

DATA_STRUCTURES_API
DS_Bool CircularBuffer_IsFull(CircularBuffer this);

DATA_STRUCTURES_API
DS_Generic CircularBuffer_GetFrontData(CircularBuffer this);

DATA_STRUCTURES_API
DS_Generic CircularBuffer_GetBackData(CircularBuffer this);

DATA_STRUCTURES_API
DS_Void CircularBuffer_PushBack(CircularBuffer this, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void CircularBuffer_PopFront(CircularBuffer this);

#endif