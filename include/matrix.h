#ifndef DATA_STRUCTURES_MATRIX_H
#define DATA_STRUCTURES_MATRIX_H

#include <stddef.h>

typedef struct Matrix Matrix;

typedef struct {
   void (*function)(void *data, void *user_data);
   void *user_data;
} MatrixUnaryCallback;

typedef struct {
   void (*function)(const void *data1, const void *data2, void *data, void *user_data);
   void *user_data;
} MatrixBinaryCallback;

__attribute__((visibility("default")))
Matrix *Matrix_Create(size_t data_size, size_t row_count, size_t column_count);

__attribute__((visibility("default")))
void Matrix_Destroy(Matrix *this);

__attribute__((visibility("default")))
void *Matrix_GetData(const Matrix *this, size_t row, size_t column);

__attribute__((visibility("default")))
size_t Matrix_GetRowCount(const Matrix *this);

__attribute__((visibility("default")))
size_t Matrix_GetColumnCount(const Matrix *this);

__attribute__((visibility("default")))
void Matrix_SetData(Matrix *this, size_t row, size_t column, const void *data);

__attribute__((visibility("default")))
Matrix *Matrix_Transposition(Matrix *this);

__attribute__((visibility("default")))
Matrix *Matrix_Multiplication(Matrix *matrix1,
   Matrix *matrix2,
   MatrixBinaryCallback binary_callback);

__attribute__((visibility("default")))
Matrix *Matrix_Operation(Matrix *matrix1,
   Matrix *matrix2,
   MatrixBinaryCallback binary_callback);

__attribute__((visibility("default")))
Matrix *Matrix_ColumnVectorization(Matrix *this);

__attribute__((visibility("default")))
void Matrix_Traverse(Matrix *this, MatrixUnaryCallback unary_callback);

#endif
