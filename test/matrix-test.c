#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <matrix.h>

static void _UnaryPrint(void *data, void *user_data);

int main(void)
{
   Matrix *obj;
   int i, value;
   MatrixUnaryCallback unary_callback;

   srand((int)time(NULL));
   unary_callback.function = _UnaryPrint;
   unary_callback.user_data = NULL;

   obj = Matrix_Create(sizeof(int), 10, 10);
   if (!obj) {
      fprintf(stderr, "Matrix_Create() failed\n");
      return 1;
   }
   printf("Matrix_Create() passed\n");

   for (i = 0; i < 10; i++) {
      value = rand() % 100;
      Matrix_SetData(matrix, 0, 0, &value);
   }
   printf("Matrix_Insert() passed\n");
   Matrix_Traverse(matrix, unary_callback);
   printf("\nMatrix_Traverse() passed\n");
   Matrix_Destroy(matrix);
   printf("Matrix_Destroy() passed\n");
   printf("All matrix tests passed!\n");

   return 0;
}

static void _UnaryPrint(void *data, void *user_data)
{
   (void)user_data;
   printf("%d ", *(int *)data);
}
