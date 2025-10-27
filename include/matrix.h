#ifndef DATA_STRUCTURES_MATRIX_H
#define DATA_STRUCTURES_MATRIX_H

#include <data-structures.h>

typedef struct Matrix * Matrix;

DATA_STRUCTURES_API
Matrix Matrix_Create(DS_Size data_size, DS_Size row_count, DS_Size column_count);

DATA_STRUCTURES_API
DS_Void Matrix_Destroy(Matrix self);

DATA_STRUCTURES_API
DS_Generic Matrix_GetData(const Matrix self, DS_Size row, DS_Size column);

DATA_STRUCTURES_API
DS_Size Matrix_GetRowCount(const Matrix self);

DATA_STRUCTURES_API
DS_Size Matrix_GetColumnCount(const Matrix self);

DATA_STRUCTURES_API
DS_Void Matrix_SetData(Matrix self, DS_Size row, DS_Size column, const DS_Generic data);

DATA_STRUCTURES_API
Matrix Matrix_Transposition(Matrix self);

DATA_STRUCTURES_API
Matrix Matrix_Multiplication(Matrix matrix1, Matrix matrix2, DS_BinaryCallback binary_callback);

DATA_STRUCTURES_API
Matrix Matrix_Operation(Matrix matrix1, Matrix matrix2, DS_BinaryCallback binary_callback);

DATA_STRUCTURES_API
Matrix Matrix_ColumnVectorization(Matrix self);

DATA_STRUCTURES_API
DS_Void Matrix_Traverse(Matrix self, DS_UnaryCallback unary_callback);

#endif