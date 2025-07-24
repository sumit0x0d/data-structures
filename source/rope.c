#include <assert.h>
#include <stdlib.h>

#include <rope.h>

typedef RopeNode Node;

struct rope_node {
     void *data;
     struct rope_node *parent;
     struct rope_node *left;
     struct rope_node *right;     
};

struct rope {
     size_t data_size;
     size_t size;
};

Rope *Rope_Create(size_t dSize)
{
     Rope *rope = (Rope *)malloc(sizeof(Rope));
     assert(rope);
     rope->data_size = dSize;
     rope->size = 0;     
     return rope;
}

void Rope_Destroy(Rope *rope)
{
     free(rope);
}
