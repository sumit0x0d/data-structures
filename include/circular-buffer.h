#ifndef DATA_STRUCTURES_CIRCULAR_BUFFER_H
#define DATA_STRUCTURES_CIRCULAR_BUFFER_H

#include <data-structures.h>

typedef struct CircularBuffer * CircularBuffer;

DATA_STRUCTURES_API
CircularBuffer CircularBuffer_Create(DS_Size data_size, DS_Size size);

DATA_STRUCTURES_API
DS_Void CircularBuffer_Destroy(CircularBuffer self);

DATA_STRUCTURES_API
DS_Bool CircularBuffer_IsEmpty(CircularBuffer self);

DATA_STRUCTURES_API
DS_Bool CircularBuffer_IsFull(CircularBuffer self);

DATA_STRUCTURES_API
DS_Generic CircularBuffer_GetFrontData(CircularBuffer self);

DATA_STRUCTURES_API
DS_Generic CircularBuffer_GetBackData(CircularBuffer self);

DATA_STRUCTURES_API
DS_Void CircularBuffer_PushBack(CircularBuffer self, const DS_Generic data);

DATA_STRUCTURES_API
DS_Void CircularBuffer_PopFront(CircularBuffer self);

#endif