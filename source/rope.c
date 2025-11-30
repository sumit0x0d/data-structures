#include <assert.h>
#include <stdlib.h>

#include <rope.h>

struct RopeNode {
     void *data;
     RopeNode *parent;
     RopeNode *left;
     RopeNode *right;
};

struct Rope {
     size_t data_size;
     size_t size;
};

Rope *Rope_Create(size_t size)
{
     Rope *this;

     this = (Rope *)malloc(sizeof(Rope));
     if (!this) {
          return NULL;
     }

     this->data_size = size;
     this->size = 0;

     return this;
}

void Rope_Destroy(Rope *this)
{
     free(this);
}
