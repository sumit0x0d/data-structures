#ifndef DATA_STRUCTURES_MATRIX_H
#define DATA_STRUCTURES_MATRIX_H

#include <data-structures.h>

typedef struct matrix Matrix;

typedef void (*MatrixOperation)(const DS_Data data1, const DS_Data data2, DS_Data data);

DS_PUBLIC_API
Matrix *DS_Matrix_Create(DS_Size sData, DS_Size nRow, DS_Size nColumn);

DS_PUBLIC_API
void DS_Matrix_Destroy(Matrix *matrix);

DS_PUBLIC_API
void *DS_Matrix_GetData(const Matrix *matrix, DS_Size row, DS_Size column);

DS_PUBLIC_API
DS_Size DS_Matrix_GetRowCount(const Matrix *matrix);

DS_PUBLIC_API
DS_Size DS_Matrix_GetColumnCount(const Matrix *matrix);

DS_PUBLIC_API
void DS_Matrix_SetData(Matrix *matrix, DS_Size row, DS_Size column, const DS_Data data);

DS_PUBLIC_API
Matrix *DS_Matrix_Transposition(Matrix *matrix);

DS_PUBLIC_API
Matrix *DS_Matrix_Multiplication(Matrix *matrix1, Matrix *matrix2, MatrixOperation moMultiplication);

DS_PUBLIC_API
Matrix *DS_Matrix_Operation(Matrix *matrix1, Matrix *matrix2, MatrixOperation mOperation);

DS_PUBLIC_API
Matrix *DS_Matrix_ColumnVectorization(Matrix *matrix);

DS_PUBLIC_API
void DS_Matrix_Traverse(Matrix *matrix, void (*traverse)(DS_Data data));

#endif
