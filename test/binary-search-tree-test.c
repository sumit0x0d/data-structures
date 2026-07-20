#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <binary-search-tree.h>

static int _CompareInt(const void *data1, const void *data2, void *user_data);
static void _UnaryPrint(void *data, void *user_data);

int main(void)
{
   BinarySearchTree *binary_search_tree;
   int i, value;
   BinarySearchTreeCompareCallback compare_callback;
   BinarySearchTreeUnaryCallback unary_callback;

   srand((int)time(NULL));
   compare_callback.function = _CompareInt;
   compare_callback.user_data = NULL;
   unary_callback.function = _UnaryPrint;
   unary_callback.user_data = NULL;

   binary_search_tree = BinarySearchTree_Create(sizeof(int), compare_callback);
   if (!binary_search_tree) {
      fprintf(stderr, "BinarySearchTree_Create() failed\n");
      return 1;
   }
   printf("BinarySearchTree_Create() passed\n");

   for (i = 0; i < 10; i++) {
      value = rand() % 100;
      BinarySearchTree_Insert(binary_search_tree, &value);
   }
   printf("BinarySearchTree_Insert() passed\n");
   BinarySearchTree_TraverseInorder(binary_search_tree, unary_callback);
   printf("\nBinarySearchTree_TraverseInorder() passed\n");
   BinarySearchTree_Destroy(binary_search_tree);
   printf("BinarySearchTree_Destroy() passed\n");
   printf("All binary-search-tree tests passed!\n");

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
