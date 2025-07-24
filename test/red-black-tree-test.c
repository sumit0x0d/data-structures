#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <red-black-tree.h>

static int _compare_int(const void *data1, const void *data2, void *uData);

int main(void)
{
     srand((int)time(NULL));
     RedBlackTree *rbtree = RedBlackTree_Create(sizeof (int), _compare_int, NULL);
     (void)rbtree;
     return 0;
}

static int _compare_int(const void *data1, const void *data2, void *uData)
{
     (void)uData;
     if (*(int *)data1 < *(int *)data2) {
          return -1;
     }
     if (*(int *)data1 > *(int *)data2) {
          return 1;
     }
     return 0;
}
