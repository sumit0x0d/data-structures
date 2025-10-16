#ifndef DATA_STRUCTURES_CIRCULAR_BUFFER_H
#define DATA_STRUCTURES_CIRCULAR_BUFFER_H

#include <data-structures.h>

typedef struct CircularBuffer * CircularBuffer;

DATA_STRUCTURES_API
CircularBuffer CircularBuffer_Create(
     DS_Size data_size,
     DS_Size size
);

DATA_STRUCTURES_API
DS_Void CircularBuffer_Destroy(
     CircularBuffer circular_buffer
);

DATA_STRUCTURES_API
DS_Bool CircularBuffer_IsEmpty(
     CircularBuffer circular_buffer
);

DATA_STRUCTURES_API
DS_Bool CircularBuffer_IsFull(
     CircularBuffer circular_buffer
);

DATA_STRUCTURES_API
DS_Generic CircularBuffer_GetFrontData(
     CircularBuffer circular_buffer
);

DATA_STRUCTURES_API
DS_Generic CircularBuffer_GetBackData(
     CircularBuffer circular_buffer
);

DATA_STRUCTURES_API
DS_Void CircularBuffer_PushBack(
     CircularBuffer circular_buffer,
     const DS_Generic data
);

DATA_STRUCTURES_API
DS_Void CircularBuffer_PopFront(
     CircularBuffer circular_buffer
);

#endif
