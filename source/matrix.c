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

Matrix Matrix_Create(DS_Size data_size, DS_Size row_count, DS_Size column_count)
{
     Matrix self;

     self = (Matrix)malloc(sizeof (struct Matrix));
     if (!self) {
          return NULL;
     };
     
     self->array = Array_Create(data_size, row_count * column_count);
     if (!self->array) {
          free(self);
          return NULL;
     };
     
     self->row_count = row_count;
     self->column_count = column_count;
     
     return self;
};

DS_Void Matrix_Destroy(Matrix self)
{
     Array_Destroy(self->array);
     free(self);
}

DS_Generic Matrix_GetData(const Matrix self, DS_Size row, DS_Size column)
{
     return Array_GetData(self->array, (row * self->column_count) + column);
}

DS_Size Matrix_GetRowCount(const Matrix self)
{
     return self->row_count;
}

DS_Size Matrix_GetColumnCount(const Matrix self)
{
     return self->column_count;
}

DS_Void Matrix_SetData(Matrix self, DS_Size row, DS_Size column, const DS_Generic data)
{
     Array_SetData(self->array, (row * self->column_count) + column, data);
}

Matrix Matrix_Transposition(Matrix self)
{
     Matrix transpose;
     DS_Size i;
     DS_Size j;

     transpose = Matrix_Create(Array_GetDataSize(self->array), self->column_count, self->row_count);
     if (!transpose) {
          return NULL;
     }
     
     for (i = 0; i < transpose->row_count; i++) {
          for (j = 0; j < transpose->column_count; j++) {
               Matrix_SetData(transpose, i, j, Matrix_GetData(self, i, j));
          }
     }
     
     return transpose;
}

Matrix Matrix_Multiplication(Matrix matrix1, Matrix matrix2, DS_BinaryCallback binary_callback)
{
     Matrix self;
     DS_Size i;
     DS_Size j;
     DS_Size k;

     if (matrix1->column_count != matrix2->row_count) {
          return NULL;
     }
     
     self = Matrix_Create(Array_GetDataSize(matrix1->array), matrix1->row_count, matrix2->column_count);
     
     for (i = 0; i < self->row_count; i++) {
          for (j = 0; j < self->column_count; j++) {
               for (k = 0; k < matrix1->column_count; k++) {
                    binary_callback.function(Matrix_GetData(self, i, j),
                         Matrix_GetData(matrix1, i, k), Matrix_GetData(matrix2, k, j));
                    (void)binary_callback.user_data;
               }
          }
     }

     return self;
}

Matrix Matrix_Operation(Matrix matrix1, Matrix matrix2, DS_BinaryCallback binary_callback)
{
     Matrix self;
     DS_Size i;
     DS_Size j;

     if (matrix1->row_count != matrix2->row_count ||
         matrix1->column_count == matrix2->column_count) {
          return NULL;   
     }
     
     self = Matrix_Create(Array_GetDataSize(matrix1->array), matrix1->row_count, matrix1->column_count);
     if (!self) {
          return NULL;
     }
     
     for (i = 0; i < matrix1->row_count; i++) {
          for (j = 0; j < matrix2->column_count; j++) {
               binary_callback.function(Matrix_GetData(self, i, j),
                    Matrix_GetData(matrix1, i, j), Matrix_GetData(matrix2, i, j));
               (void)binary_callback.user_data;
          }
     }

     return self;
}

Matrix Matrix_ColumnVectorization(Matrix self)
{
     Matrix vectorize;
     DS_Size i;
     DS_Size j;

     vectorize = Matrix_Create(Array_GetDataSize(self->array), self->row_count * self->column_count, 1);
     if (!vectorize) {
          return NULL;
     }
     
     for (i = 0; i < self->row_count; i++) {
          for (j = 0; j < self->column_count; j++) {
               Matrix_SetData(vectorize, (i * self->column_count) + j, 0, Matrix_GetData(self, i, j));
          }
     }

     return vectorize;
}

DS_Void Matrix_Traverse(Matrix self, DS_UnaryCallback unary_callback)
{
     DS_Size i;
     DS_Size j;

     for (i = 0; i < self->row_count; i++) {
          for (j = 0; j < self->column_count; j++) {
               unary_callback.function(Matrix_GetData(self, i, j), unary_callback.user_data);
          }
     }
}
