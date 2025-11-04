#ifndef DATA_STRUCTURES_ROPE_H
#define DATA_STRUCTURES_ROPE_H



typedef struct Rope * Rope;
typedef struct RopeNode * RopeNode;

__attribute__((visibility("default")))
Rope Rope_Create(size_t data_size);

__attribute__((visibility("default")))
void Rope_Destroy(Rope this);

#endif
