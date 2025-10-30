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
     Rope this;

     this = (Rope)malloc(sizeof(struct Rope));
     if (!this) {
          return NULL;
     }

     this->data_size = size;
     this->size = 0;    
     
     return this;
}

DS_Void Rope_Destroy(Rope this)
{
     free(this);
}
