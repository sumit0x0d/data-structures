#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <array.h>
#include <matrix.h>

typedef MatrixOperation Operation;

struct matrix {
     Array *array;
     DS_Size row_count;
     DS_Size column_count;
};

Matrix *DS_Matrix_Create(DS_Size sData, DS_Size nRow, DS_Size nColumn)
{
     Matrix *matrix = (Matrix *)malloc(sizeof (Matrix));
     if (!matrix) {
          return NULL;
     }
     matrix->array = Array_Create(sData, nRow * nColumn);
     if (!matrix->array) {
          free(matrix);
          return NULL;
     }
     matrix->row_count = nRow;
     matrix->column_count = nColumn;
     return matrix;
}

void DS_Matrix_Destroy(Matrix *matrix)
{
     Array_Destroy(matrix->array);
     free(matrix);
}

void *DS_Matrix_GetData(const Matrix *matrix, DS_Size row, DS_Size column)
{
     return Array_GetData(matrix->array, (row * matrix->column_count) + column);
}

DS_Size DS_Matrix_GetRowCount(const Matrix *matrix)
{
     return matrix->row_count;
}

DS_Size DS_Matrix_GetColumnCount(const Matrix *matrix)
{
     return matrix->column_count;
}

void DS_Matrix_SetData(Matrix *matrix, DS_Size row, DS_Size column, const DS_Data data)
{
     Array_SetData(matrix->array, (row * matrix->column_count) + column, data);
}

Matrix *DS_Matrix_Transposition(Matrix *matrix)
{
     Matrix *tMatrix = DS_Matrix_Create(Array_GetDataSize(matrix->array), matrix->column_count, matrix->row_count);
     if (!tMatrix) {
          return NULL;
     }
     for (DS_Size i = 0; i < tMatrix->row_count; i++) {
          for (DS_Size j = 0; j < tMatrix->column_count; j++) {
               DS_Matrix_SetData(tMatrix, i, j, DS_Matrix_GetData(matrix, i, j));
          }
     }
     return tMatrix;
}

Matrix *DS_Matrix_Multiplication(Matrix *matrix1, Matrix *matrix2, Operation multiplication)
{
     if (matrix1->column_count != matrix2->row_count) {
          return NULL;
     }
     Matrix *matrix = DS_Matrix_Create(Array_GetDataSize(matrix1->array), matrix1->row_count, matrix2->column_count);
     for (DS_Size i = 0; i < matrix->row_count; i++) {
          for (DS_Size j = 0; j < matrix->column_count; j++) {
               for (DS_Size k = 0; k < matrix1->column_count; k++) {
                    multiplication(DS_Matrix_GetData(matrix, i, j), DS_Matrix_GetData(matrix1, i, k), DS_Matrix_GetData(matrix2, k, j));
               }
          }
     }
     return matrix;
}

Matrix *DS_Matrix_Operation(Matrix *matrix1, Matrix *matrix2, Operation operation)
{
     assert(matrix1->row_count == matrix2->row_count);
     assert(matrix1->column_count == matrix2->column_count);
     Matrix *matrix = DS_Matrix_Create(Array_GetDataSize(matrix1->array), matrix1->row_count, matrix1->column_count);
     assert(matrix);
     for (DS_Size i = 0; i < matrix1->row_count; i++) {
          for (DS_Size j = 0; j < matrix2->column_count; j++) {
               operation(DS_Matrix_GetData(matrix, i, j), DS_Matrix_GetData(matrix1, i, j), DS_Matrix_GetData(matrix2, i, j));
          }
     }
     return matrix;
}

Matrix *DS_Matrix_ColumnVectorization(Matrix *matrix)
{
     Matrix *vMatrix = DS_Matrix_Create(Array_GetDataSize(matrix->array), matrix->row_count * matrix->column_count, 1);
     if (!vMatrix) {
          return NULL;
     }
     for (DS_Size i = 0; i < matrix->row_count; i++) {
          for (DS_Size j = 0; j < matrix->column_count; j++) {
               DS_Matrix_SetData(vMatrix, (i * matrix->column_count) + j, 0, DS_Matrix_GetData(matrix, i, j));
          }
     }
     return vMatrix;
}

void DS_Matrix_Traverse(Matrix *matrix, void (*traverse)(DS_Data data))
{
     for (DS_Size i = 0; i < matrix->row_count; i++) {
          for (DS_Size j = 0; j < matrix->column_count; j++) {
               traverse(DS_Matrix_GetData(matrix, i, j));
          }
     }
}
