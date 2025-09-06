#include <assert.h>
#include <stdlib.h>

#include <rope.h>

typedef RopeNode Node;

struct rope_node {
     DS_Data data;
     struct rope_node *parent;
     struct rope_node *left;
     struct rope_node *right;     
};

struct rope {
     DS_Size data_size;
     DS_Size size;
};

Rope *Rope_Create(DS_Size size)
{
     Rope *rope = (Rope *)malloc(sizeof(Rope));
     assert(rope);
     rope->data_size = size;
     rope->size = 0;     
     return rope;
}

void Rope_Destroy(Rope *rope)
{
     free(rope);
}
