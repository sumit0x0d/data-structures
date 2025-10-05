#ifndef DATA_STRUCTURES_MATRIX_H
#define DATA_STRUCTURES_MATRIX_H

#include <data-structures.h>

typedef struct Matrix * Matrix;

DATA_STRUCTURES_API
Matrix Matrix_Create(
     DS_Size data_size,
     DS_Size row_count,
     DS_Size column_count
);

DATA_STRUCTURES_API
DS_Void Matrix_Destroy(
     Matrix matrix
);

DATA_STRUCTURES_API
DS_Generic Matrix_GetData(
     const Matrix matrix,
     DS_Size      row,
     DS_Size      column
);

DATA_STRUCTURES_API
DS_Size Matrix_GetRowCount(
     const Matrix matrix
);

DATA_STRUCTURES_API
DS_Size Matrix_GetColumnCount(
     const Matrix matrix
);

DATA_STRUCTURES_API
DS_Void Matrix_SetData(
     Matrix           matrix,
     DS_Size          row,
     DS_Size          column,
     const DS_Generic data
);

DATA_STRUCTURES_API
Matrix Matrix_Transposition(
     Matrix matrix
);

DATA_STRUCTURES_API
Matrix Matrix_Multiplication(
     Matrix            matrix1,
     Matrix            matrix2,
     DS_CallbackBinary binary_callback,
     DS_Generic        binary_context
);

DATA_STRUCTURES_API
Matrix Matrix_Operation(
     Matrix            matrix1,
     Matrix            matrix2,
     DS_CallbackBinary binary_callback,
     DS_Generic        binary_context
);

DATA_STRUCTURES_API
Matrix Matrix_ColumnVectorization(
     Matrix matrix
);

DATA_STRUCTURES_API
DS_Void Matrix_Traverse(
     Matrix           matrix,
     DS_CallbackUnary unary_callback,
     DS_Generic       unary_context
);

#endif