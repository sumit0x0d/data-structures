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
     Rope self;

     self = (Rope)malloc(sizeof(struct Rope));
     if (!self) {
          return NULL;
     }

     self->data_size = size;
     self->size = 0;    
     
     return self;
}

DS_Void Rope_Destroy(Rope self)
{
     free(self);
}
