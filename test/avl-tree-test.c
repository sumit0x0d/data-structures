#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <avl-tree.h>

static int _compare_int(const void *data1, const void *data2, void *uData);
static void _print_int(void *data, void *uData);

int main()
{
     srand((int)time(NULL));
     AvlTree *aTree = AvlTree_Create(sizeof (int), _compare_int, NULL);
     for (int i = 0; i < 10; i++) {
           int a = rand() % 100;
           printf("Inserting %d\n", a);
           AvlTree_Insert(aTree, &a);
     }
     AvlTree_TraverseInorder(aTree, _print_int, NULL);
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

static void _print_int(void *data, void *uData)
{
     (void)uData;
     printf("%d ", *(int *)data);
}
