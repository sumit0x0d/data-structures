#include <assert.h>
#include <stdlib.h>

#include <rope.h>

struct RopeNode {
     DS_Generic data;
     RopeNode parent;
     RopeNode left;
     RopeNode right;    
};

struct Rope {
     DS_Size data_size;
     DS_Size size;
};

Rope Rope_Create(DS_Size size)
{
     Rope rope = (Rope)malloc(sizeof(struct Rope));
     assert(rope);
     rope->data_size = size;
     rope->size = 0;    
     return rope;
}

DS_Void Rope_Destroy(Rope *rope)
{
     free(rope);
}
