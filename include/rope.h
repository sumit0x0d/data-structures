#ifndef DATA_STRUCTURES_ROPE_H
#define DATA_STRUCTURES_ROPE_H

#include <data-structures.h>

typedef struct Rope * Rope;
typedef struct RopeNode * RopeNode;

DATA_STRUCTURES_API
Rope Rope_Create(DS_Size data_size);

DATA_STRUCTURES_API
DS_Void Rope_Destroy(Rope this);

#endif
