#ifndef DATA_STRUCTURES_MATRIX_H
#define DATA_STRUCTURES_MATRIX_H

#include <data-structures.h>

typedef struct matrix * Matrix;

typedef void (*MatrixOperation)(const DS_Data data1, const DS_Data data2, DS_Data data);

DS_PUBLIC_API
Matrix Matrix_Create(DS_Size sData, DS_Size nRow, DS_Size nColumn);

DS_PUBLIC_API
void Matrix_Destroy(Matrix matrix);

DS_PUBLIC_API
DS_Data Matrix_GetData(const Matrix matrix, DS_Size row, DS_Size column);

DS_PUBLIC_API
DS_Size Matrix_GetRowCount(const Matrix matrix);

DS_PUBLIC_API
DS_Size Matrix_GetColumnCount(const Matrix matrix);

DS_PUBLIC_API
void Matrix_SetData(Matrix matrix, DS_Size row, DS_Size column, const DS_Data data);

DS_PUBLIC_API
Matrix Matrix_Transposition(Matrix matrix);

DS_PUBLIC_API
Matrix Matrix_Multiplication(Matrix matrix1, Matrix matrix2, MatrixOperation operation);

DS_PUBLIC_API
Matrix Matrix_Operation(Matrix matrix1, Matrix matrix2, MatrixOperation operation);

DS_PUBLIC_API
Matrix Matrix_ColumnVectorization(Matrix matrix);

DS_PUBLIC_API
void Matrix_Traverse(Matrix matrix, DS_FunctionTraverse fTraverse, DS_Context context);

#endif
