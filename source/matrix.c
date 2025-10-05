#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <array.h>
#include <matrix.h>

struct Matrix {
     Array array;
     DS_Size row_count;
     DS_Size column_count;
};

Matrix Matrix_Create(
     DS_Size data_size,
     DS_Size row_count,
     DS_Size column_count
) {
     Matrix matrix = (Matrix)malloc(sizeof (struct Matrix));
     if (!matrix) {
          return NULL;
     }
     matrix->array = Array_Create(data_size, row_count * column_count);
     if (!matrix->array) {
          free(matrix);
          return NULL;
     }
     matrix->row_count = row_count;
     matrix->column_count = column_count;
     return matrix;
}

DS_Void Matrix_Destroy(
     Matrix matrix
) {
     Array_Destroy(matrix->array);
     free(matrix);
}

DS_Generic Matrix_GetData(
     const Matrix matrix,
     DS_Size      row,
     DS_Size      column
) {
     return Array_GetData(matrix->array, (row * matrix->column_count) + column);
}

DS_Size Matrix_GetRowCount(
     const Matrix matrix
) {
     return matrix->row_count;
}

DS_Size Matrix_GetColumnCount(
     const Matrix matrix
) {
     return matrix->column_count;
}

DS_Void Matrix_SetData(
     Matrix           matrix,
     DS_Size          row,
     DS_Size          column,
     const DS_Generic data
) {
     Array_SetData(matrix->array, (row * matrix->column_count) + column, data);
}

Matrix Matrix_Transposition(
     Matrix matrix
) {
     Matrix transpose =
          Matrix_Create(Array_GetDataSize(matrix->array),
                        matrix->column_count, matrix->row_count);
     if (!transpose) {
          return NULL;
     }
     for (DS_Size i = 0; i < transpose->row_count; i++) {
          for (DS_Size j = 0; j < transpose->column_count; j++) {
               Matrix_SetData(transpose, i, j, Matrix_GetData(matrix, i, j));
          }
     }
     return transpose;
}

Matrix Matrix_Multiplication(
     Matrix            matrix1,
     Matrix            matrix2,
     DS_CallbackBinary binary_callback,
     DS_Generic        binary_context
) {
     if (matrix1->column_count != matrix2->row_count) {
          return NULL;
     }
     Matrix matrix =
          Matrix_Create(Array_GetDataSize(matrix1->array), matrix1->row_count,
                        matrix2->column_count);
     for (DS_Size i = 0; i < matrix->row_count; i++) {
          for (DS_Size j = 0; j < matrix->column_count; j++) {
               for (DS_Size k = 0; k < matrix1->column_count; k++) {
                    binary_callback(Matrix_GetData(matrix, i, j),
                                   Matrix_GetData(matrix1, i, k),
                                   Matrix_GetData(matrix2, k, j));
                    (void)binary_context;
               }
          }
     }
     return matrix;
}

Matrix Matrix_Operation(
     Matrix            matrix1,
     Matrix            matrix2,
     DS_CallbackBinary binary_callback,
     DS_Generic        binary_context
) {
     if (matrix1->row_count != matrix2->row_count ||
         matrix1->column_count == matrix2->column_count) {
          return NULL;   
     }
     Matrix matrix = Matrix_Create(Array_GetDataSize(matrix1->array), matrix1->row_count,
                    matrix1->column_count);
     if (!matrix) {
          return NULL;
     }
     for (DS_Size i = 0; i < matrix1->row_count; i++) {
          for (DS_Size j = 0; j < matrix2->column_count; j++) {
               binary_callback(Matrix_GetData(matrix, i, j),
                              Matrix_GetData(matrix1, i, j),
                              Matrix_GetData(matrix2, i, j));
               (void)binary_context;
          }
     }
     return matrix;
}

Matrix Matrix_ColumnVectorization(
     Matrix matrix
) {
     Matrix vectorize = Matrix_Create(Array_GetDataSize(matrix->array),
                    matrix->row_count * matrix->column_count, 1);
     if (!vectorize) {
          return NULL;
     }
     for (DS_Size i = 0; i < matrix->row_count; i++) {
          for (DS_Size j = 0; j < matrix->column_count; j++) {
               Matrix_SetData(vectorize, (i * matrix->column_count) + j, 0,
                              Matrix_GetData(matrix, i, j));
          }
     }
     return vectorize;
}

DS_Void Matrix_Traverse(
     Matrix           matrix,
     DS_CallbackUnary unary_callback,
     DS_Generic       unary_context
) {
     for (DS_Size i = 0; i < matrix->row_count; i++) {
          for (DS_Size j = 0; j < matrix->column_count; j++) {
               unary_callback(Matrix_GetData(matrix, i, j), unary_context);
          }
     }
}
