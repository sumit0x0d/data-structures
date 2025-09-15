#ifndef DATA_STRUCTURES_ROPE_H
#define DATA_STRUCTURES_ROPE_H

#include <data-structures.h>

typedef struct rope * Rope;
typedef struct rope_node * RopeNode;

DS_API
Rope Rope_Create(DS_Size sData);

DS_API
void Rope_Destroy(Rope rope);

#endif
