#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <matrix.h>

struct Matrix {
     void *base;
     size_t data_size;
     size_t capacity;
     size_t row_count;
     size_t column_count;
};

Matrix *Matrix_Create(size_t data_size, size_t row_count, size_t column_count)
{
     Matrix *this;

     this = (Matrix *)malloc(sizeof (Matrix));
     if (!this) {
          return NULL;
     };

     this->capacity = row_count * column_count;

     this->base = malloc(data_size * this->capacity);
     if (!this->base) {
          free(this);
          return NULL;
     };

     this->data_size = data_size;
     this->row_count = row_count;
     this->column_count = column_count;

     return this;
};

void Matrix_Destroy(Matrix *this)
{
     free(this->base);
     free(this);
}

void *Matrix_GetData(const Matrix *this, size_t row, size_t column)
{
     return (char *)this->base + (this->data_size * (row * this->column_count) + column);
}

size_t Matrix_GetRowCount(const Matrix *this)
{
     return this->row_count;
}

size_t Matrix_GetColumnCount(const Matrix *this)
{
     return this->column_count;
}

void Matrix_SetData(Matrix *this, size_t row, size_t column, const void *data)
{
     memcpy(Matrix_GetData(this, row, column), data, this->data_size);
}

Matrix *Matrix_Transposition(Matrix *this)
{
     Matrix *transpose;
     size_t i;
     size_t j;

     transpose = Matrix_Create(this->data_size, this->column_count, this->row_count);
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

Matrix *Matrix_Multiplication(Matrix *matrix1, Matrix *matrix2, MatrixBinaryCallback binary_callback)
{
     Matrix *this;
     size_t i;
     size_t j;
     size_t k;

     if (matrix1->column_count != matrix2->row_count) {
          return NULL;
     }

     this = Matrix_Create(matrix1->data_size, matrix1->row_count, matrix2->column_count);

     for (i = 0; i < this->row_count; i++) {
          for (j = 0; j < this->column_count; j++) {
               for (k = 0; k < matrix1->column_count; k++) {
                    binary_callback.function(Matrix_GetData(this, i, j),
                         Matrix_GetData(matrix1, i, k),
                         Matrix_GetData(this, k, j),
                         binary_callback.user_data);
               }
          }
     }

     return this;
}

Matrix *Matrix_Operation(Matrix *matrix1, Matrix *matrix2, MatrixBinaryCallback binary_callback)
{
     Matrix *this;
     size_t i;
     size_t j;

     if (matrix1->row_count != matrix2->row_count || matrix1->column_count == matrix2->column_count) {
          return NULL;
     }

     this = Matrix_Create(matrix1->data_size, matrix1->row_count, matrix1->column_count);
     if (!this) {
          return NULL;
     }

     for (i = 0; i < matrix1->row_count; i++) {
          for (j = 0; j < matrix2->column_count; j++) {
               binary_callback.function(Matrix_GetData(this, i, j),
                    Matrix_GetData(matrix1, i, j),
                    Matrix_GetData(this, i, j),
                    binary_callback.user_data);
          }
     }

     return this;
}

Matrix *Matrix_ColumnVectorization(Matrix *this)
{
     Matrix *vectorize;
     size_t i;
     size_t j;

     vectorize = Matrix_Create(this->data_size, this->row_count * this->column_count, 1);
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

void Matrix_Traverse(Matrix *this, MatrixUnaryCallback unary_callback)
{
     size_t i;
     size_t j;

     for (i = 0; i < this->row_count; i++) {
          for (j = 0; j < this->column_count; j++) {
               unary_callback.function(Matrix_GetData(this, i, j), unary_callback.user_data);
          }
     }
}
