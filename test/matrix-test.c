#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <matrix.h>

static void _print_int(void *data);
static void _muliply_by(void *data);

int main()
{
     srand((int)time(NULL));
     Matrix *matrix = Matrix_Create(sizeof (int), 10, 10);
     for (int i = 0; i < 10; i++) {
          for (size_t j = 0; j < 10; j++) {
               int a = rand() % 100;
               Matrix_SetData(matrix, i, j, &a);
          }
     }
     // printf("Row Count : %zu\n", matrix->row_count);
     // printf("Column Count : %zu\n", matrix->column_count);

     Matrix_Traverse(matrix, _print_int);
     Matrix_Traverse(matrix, _muliply_by);
     printf("\n");
     Matrix_Traverse(matrix, _print_int);
     return 0;
}

static void _print_int(void *data)
{
     printf("%d ", *(int *)data);
}

static void _muliply_by(void *data)
{
     *(int *)data = *(int *)data * 2;
}
