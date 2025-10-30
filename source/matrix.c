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
     Matrix this;

     this = (Matrix)malloc(sizeof (struct Matrix));
     if (!this) {
          return NULL;
     };
     
     this->array = Array_Create(data_size, row_count * column_count);
     if (!this->array) {
          free(this);
          return NULL;
     };
     
     this->row_count = row_count;
     this->column_count = column_count;
     
     return this;
};

DS_Void Matrix_Destroy(Matrix this)
{
     Array_Destroy(this->array);
     free(this);
}

DS_Generic Matrix_GetData(const Matrix this, DS_Size row, DS_Size column)
{
     return Array_GetData(this->array, (row * this->column_count) + column);
}

DS_Size Matrix_GetRowCount(const Matrix this)
{
     return this->row_count;
}

DS_Size Matrix_GetColumnCount(const Matrix this)
{
     return this->column_count;
}

DS_Void Matrix_SetData(Matrix this, DS_Size row, DS_Size column, const DS_Generic data)
{
     Array_SetData(this->array, (row * this->column_count) + column, data);
}

Matrix Matrix_Transposition(Matrix this)
{
     Matrix transpose;
     DS_Size i;
     DS_Size j;

     transpose = Matrix_Create(Array_GetDataSize(this->array), this->column_count, this->row_count);
     if (!transpose) {
          return NULL;
     }

     for (i = 0; i < transpose->row_count; i++) {
          for (j = 0; j < transpose->column_count; j++) {
               Matrix_SetData(transpose, i, j, Matrix_GetData(this, i, j));
          }
     }

     return transpose;
}

Matrix Matrix_Multiplication(Matrix matrix1, Matrix matrix2, DS_BinaryCallback binary_callback)
{
     Matrix this;
     DS_Size i;
     DS_Size j;
     DS_Size k;

     if (matrix1->column_count != matrix2->row_count) {
          return NULL;
     }
     
     this = Matrix_Create(Array_GetDataSize(matrix1->array), matrix1->row_count, matrix2->column_count);
     
     for (i = 0; i < this->row_count; i++) {
          for (j = 0; j < this->column_count; j++) {
               for (k = 0; k < matrix1->column_count; k++) {
                    binary_callback.function(Matrix_GetData(this, i, j), Matrix_GetData(matrix1, i, k),
                         Matrix_GetData(this, k, j), binary_callback.user_data);
                    ;
               }
          }
     }

     return this;
}

Matrix Matrix_Operation(Matrix matrix1, Matrix matrix2, DS_BinaryCallback binary_callback)
{
     Matrix this;
     DS_Size i;
     DS_Size j;

     if (matrix1->row_count != matrix2->row_count ||
         matrix1->column_count == matrix2->column_count) {
          return NULL;   
     }
     
     this = Matrix_Create(Array_GetDataSize(matrix1->array), matrix1->row_count, matrix1->column_count);
     if (!this) {
          return NULL;
     }
     
     for (i = 0; i < matrix1->row_count; i++) {
          for (j = 0; j < matrix2->column_count; j++) {
               binary_callback.function(Matrix_GetData(this, i, j), Matrix_GetData(matrix1, i, j),
                    Matrix_GetData(this, i, j), binary_callback.user_data);
               ;
          }
     }

     return this;
}

Matrix Matrix_ColumnVectorization(Matrix this)
{
     Matrix vectorize;
     DS_Size i;
     DS_Size j;

     vectorize = Matrix_Create(Array_GetDataSize(this->array), this->row_count * this->column_count, 1);
     if (!vectorize) {
          return NULL;
     }
     
     for (i = 0; i < this->row_count; i++) {
          for (j = 0; j < this->column_count; j++) {
               Matrix_SetData(vectorize, (i * this->column_count) + j, 0, Matrix_GetData(this, i, j));
          }
     }

     return vectorize;
}

DS_Void Matrix_Traverse(Matrix this, DS_UnaryCallback unary_callback)
{
     DS_Size i;
     DS_Size j;

     for (i = 0; i < this->row_count; i++) {
          for (j = 0; j < this->column_count; j++) {
               unary_callback.function(Matrix_GetData(this, i, j), unary_callback.user_data);
          }
     }
}
