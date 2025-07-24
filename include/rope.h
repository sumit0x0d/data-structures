#ifndef DATA_STRUCTURES_ROPE_H
#define DATA_STRUCTURES_ROPE_H

#include <stddef.h>

typedef struct rope Rope;
typedef struct rope_node RopeNode;

Rope *Rope_Create(size_t dSize);
void Rope_Destroy(Rope *rope);

#endif
