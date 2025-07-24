#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <array.h>
#include <matrix.h>

typedef MatrixOperation Operation;

struct matrix {
     Array *array;
     size_t row_count;
     size_t column_count;
};

Matrix *Matrix_Create(size_t dSize, size_t rCount, size_t cCount)
{
     Matrix *matrix = (Matrix *)malloc(sizeof (Matrix));
     assert(matrix);
     matrix->array = Array_Create(dSize, rCount * cCount);
     assert(matrix->array);
     matrix->row_count = rCount;
     matrix->column_count = cCount;
     return matrix;
}

void Matrix_Destroy(Matrix *matrix)
{
     Array_Destroy(matrix->array);
     free(matrix);
}

void *Matrix_GetData(const Matrix *matrix, size_t row, size_t column)
{
     return Array_GetData(matrix->array, (row * matrix->column_count) + column);
}

size_t Matrix_GetRowCount(const Matrix *matrix)
{
     return matrix->row_count;
}

size_t Matrix_GetColumnCount(const Matrix *matrix)
{
     return matrix->column_count;
}

void Matrix_SetData(Matrix *matrix, size_t row, size_t column, const void *data)
{
     Array_SetData(matrix->array, (row * matrix->column_count) + column, data);
}

Matrix *Matrix_Transposition(Matrix *matrix)
{
     Matrix *tMatrix = Matrix_Create(Array_GetDataSize(matrix->array), matrix->column_count, matrix->row_count);
     assert(tMatrix);
     for (size_t i = 0; i < tMatrix->row_count; i++) {
          for (size_t j = 0; j < tMatrix->column_count; j++) {
               Matrix_SetData(tMatrix, i, j, Matrix_GetData(matrix, i, j));
          }
     }
     return tMatrix;
}

Matrix *Matrix_Multiplication(Matrix *matrix1, Matrix *matrix2, Operation multiplication)
{
     assert(matrix1->column_count == matrix2->row_count);
     Matrix *matrix = Matrix_Create(Array_GetDataSize(matrix1->array), matrix1->row_count, matrix2->column_count);
     for (size_t i = 0; i < matrix->row_count; i++) {
          for (size_t j = 0; j < matrix->column_count; j++) {
               for (size_t k = 0; k < matrix1->column_count; k++) {
                    multiplication(Matrix_GetData(matrix, i, j), Matrix_GetData(matrix1, i, k), Matrix_GetData(matrix2, k, j));
               }
          }
     }
     return matrix;
}

Matrix *Matrix_Operation(Matrix *matrix1, Matrix *matrix2, Operation operation)
{
     assert(matrix1->row_count == matrix2->row_count);
     assert(matrix1->column_count == matrix2->column_count);
     Matrix *matrix = Matrix_Create(Array_GetDataSize(matrix1->array), matrix1->row_count, matrix1->column_count);
     assert(matrix);
     for (size_t i = 0; i < matrix1->row_count; i++) {
          for (size_t j = 0; j < matrix2->column_count; j++) {
               operation(Matrix_GetData(matrix, i, j), Matrix_GetData(matrix1, i, j), Matrix_GetData(matrix2, i, j));
          }
     }
     return matrix;
}

Matrix *Matrix_ColumnVectorization(Matrix *matrix)
{
     Matrix *vMatrix = Matrix_Create(Array_GetDataSize(matrix->array), matrix->row_count * matrix->column_count, 1);
     assert(vMatrix);
     for (size_t i = 0; i < matrix->row_count; i++) {
          for (size_t j = 0; j < matrix->column_count; j++) {
               Matrix_SetData(vMatrix, (i * matrix->column_count) + j, 0, Matrix_GetData(matrix, i, j));
          }
     }
     return vMatrix;
}

void Matrix_Traverse(Matrix *matrix, void (*traverse)(void *data))
{
     for (size_t i = 0; i < matrix->row_count; i++) {
          for (size_t j = 0; j < matrix->column_count; j++) {
               traverse(Matrix_GetData(matrix, i, j));
          }
     }
}
