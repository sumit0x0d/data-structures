#ifndef DATA_STRUCTURES_MATRIX_H
#define DATA_STRUCTURES_MATRIX_H

#include <stddef.h>

typedef struct matrix Matrix;
typedef void (*MatrixOperation)(void *data, const void *data1, const void *data2);

Matrix *Matrix_Create(size_t dsize, size_t rcount, size_t ccount);
void Matrix_Destroy(Matrix *matrix);

void *Matrix_GetData(const Matrix *matrix, size_t row, size_t column);
size_t Matrix_GetRowCount(const Matrix *matrix);
size_t Matrix_GetColumnCount(const Matrix *matrix);

void Matrix_SetData(Matrix *matrix, size_t row, size_t column, const void *data);

Matrix *Matrix_Transposition(Matrix *matrix);
Matrix *Matrix_Multiplication(Matrix *matrix1, Matrix *matrix2, MatrixOperation moMultiplication);
Matrix *Matrix_Operation(Matrix *matrix1, Matrix *matrix2, MatrixOperation mOperation);
Matrix *Matrix_ColumnVectorization(Matrix *matrix);

void Matrix_Traverse(Matrix *matrix, void (*traverse)(void *data));

#endif
