#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <red-black-tree.h>

static int _CompareInt(const void *data1, const void *data2, void *user_data);
static void _UnaryPrint(void *data, void *user_data);

int main(void)
{
   RedBlackTree *obj;
   int i, value;
   RedBlackTreeCompareCallback compare_callback;
   RedBlackTreeUnaryCallback unary_callback;

   srand((int)time(NULL));
   compare_callback.function = _CompareInt;
   compare_callback.user_data = NULL;
   unary_callback.function = _UnaryPrint;
   unary_callback.user_data = NULL;

   obj = RedBlackTree_Create(sizeof(int), compare_callback);
   if (!obj) {
      fprintf(stderr, "RedBlackTree_Create() failed\n");
      return 1;
   }
   printf("RedBlackTree_Create() passed\n");

   for (i = 0; i < 10; i++) {
      value = rand() % 100;
      RedBlackTree_Insert(rbtree, &value);
   }
   printf("RedBlackTree_Insert() passed\n");
   RedBlackTree_Traverse(rbtree, unary_callback);
   printf("\nRedBlackTree_Traverse() passed\n");
   RedBlackTree_Destroy(rbtree);
   printf("RedBlackTree_Destroy() passed\n");
   printf("All red-black-tree tests passed!\n");

   return 0;
}

static int _CompareInt(const void *data1, const void *data2, void *user_data)
{
   (void)user_data;
   if (*(int *)data1 < *(int *)data2) return -1;
   if (*(int *)data1 > *(int *)data2) return 1;
   return 0;
}

static void _UnaryPrint(void *data, void *user_data)
{
   (void)user_data;
   printf("%d ", *(int *)data);
}
