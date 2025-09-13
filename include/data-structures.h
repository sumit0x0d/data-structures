#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#define DS_PUBLIC_API  __attribute__((visibility("default")))
#define DS_PRIVATE_API __attribute__((visibility("hidden")))

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

typedef void *    DS_Data;
typedef void *    DS_Context;
typedef DS_UInt64 DS_Size;

typedef enum {
    DS_COMPARE_LESS    = -1,
    DS_COMPARE_EQUAL   = 0,
    DS_COMPARE_GREATER = 1
} DS_Compare;

typedef void       (*DS_FunctionTraverse)(DS_Data data, DS_Context context);
typedef DS_Compare (*DS_FunctionCompare)(const DS_Data data1, const DS_Data data2, DS_Context context);
typedef DS_Size    (*DS_FunctionHash)(const DS_Data data, DS_Size sData, DS_Context context);

#endif