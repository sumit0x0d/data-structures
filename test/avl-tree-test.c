#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <avl-tree.h>

static AvlTreeCompare _CompareInt(const void *data1, const void *data2, void *user_data);
static void _UnaryPrint(void *data, void *user_data);

int main(void)
{
   AvlTree *obj;
   int i, value;
   AvlTreeCompareCallback compare_callback;
   AvlTreeUnaryCallback unary_callback;

   srand((int)time(NULL));
   compare_callback.function = _CompareInt;
   compare_callback.user_data = NULL;
   unary_callback.function = _UnaryPrint;
   unary_callback.user_data = NULL;

   obj = AvlTree_Create(sizeof(int), compare_callback);
   if (!obj) {
      fprintf(stderr, "AvlTree_Create() failed\n");
      return 1;
   }
   printf("AvlTree_Create() passed\n");

   for (i = 0; i < 10; i++) {
      value = rand() % 100;
      AvlTree_Insert(tree, &value);
   }
   printf("AvlTree_Insert() passed\n");
   AvlTree_Traverse(tree, unary_callback);
   printf("\nAvlTree_Traverse() passed\n");
   AvlTree_Destroy(tree);
   printf("AvlTree_Destroy() passed\n");
   printf("All avl-tree tests passed!\n");

   return 0;
}

static AvlTreeCompare _CompareInt(const void *data1, const void *data2, void *user_data)
{
   (void)user_data;
   if (*(int *)data1 < *(int *)data2) return AVL_TREE_COMPARE_LESS;
   if (*(int *)data1 > *(int *)data2) return AVL_TREE_COMPARE_GREATER;
   return AVL_TREE_COMPARE_EQUAL;
}

static void _UnaryPrint(void *data, void *user_data)
{
   (void)user_data;
   printf("%d ", *(int *)data);
}
