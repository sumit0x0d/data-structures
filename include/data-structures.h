#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#define DATA_STRUCTURES_API  __attribute__((visibility("default")))

typedef void DS_Void;

typedef char  DS_Int8;
typedef short DS_Int16;
typedef int   DS_Int32;
typedef long  DS_Int64;

typedef unsigned char  DS_UInt8;
typedef unsigned short DS_UInt16;
typedef unsigned int   DS_UInt32;
typedef unsigned long  DS_UInt64;

typedef float  DS_Float32;
typedef double DS_Float64;

typedef DS_UInt8 DS_Bool;
#define DS_TRUE  1
#define DS_FALSE 0

typedef const DS_UInt8 * DS_String;

typedef void * DS_Generic;

typedef DS_UInt64 DS_Size;
#define DS_OFFSET(type, member) ((DS_Size) & (((type)0)->member))

typedef enum {
    DS_COMPARE_LESS    = -1,
    DS_COMPARE_EQUAL    = 0,
    DS_COMPARE_GREATER = 1
} DS_Compare;

typedef void (*DS_CallbackUnary)(DS_Generic data, DS_Generic unary_context);
typedef void (*DS_CallbackBinary)(DS_Generic data1, DS_Generic data2,
                                  DS_Generic binary_context);

typedef DS_Compare (*DS_CallbackCompare)(const DS_Generic data1, const DS_Generic data2,
                                         DS_Generic compare_context);
typedef DS_Size (*DS_CallbackHash)(const DS_Generic data, DS_Size size,
                                   DS_Generic hash_context);

#endif