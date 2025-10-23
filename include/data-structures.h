#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#define DATA_STRUCTURES_API __attribute__((visibility("default")))

typedef void DS_Void;

typedef char DS_Int8;
typedef short DS_Int16;
typedef int DS_Int32;
typedef long DS_Int64;

typedef unsigned char DS_UInt8;
typedef unsigned short DS_UInt16;
typedef unsigned int DS_UInt32;
typedef unsigned long DS_UInt64;

typedef float DS_Float32;
typedef double DS_Float64;

typedef enum {
     DS_BOOL_FALSE = -1,
     DS_BOOL_UNKNOWN = 0,
     DS_BOOL_TRUE = 1
} DS_Bool;

typedef void * DS_Generic;

typedef DS_UInt64 DS_Size;
#define DS_OFFSET(type, member) ((DS_Size) & (((type)0)->member))

typedef struct {
     DS_Void (*function)(DS_Generic data, DS_Generic user_data);
     DS_Generic user_data;
} DS_UnaryCallback;

typedef struct {
     DS_Void (*function)(DS_Generic data1, DS_Generic data2, DS_Generic user_data);
     DS_Generic user_data;
} DS_BinaryCallback;

typedef enum {
     DS_COMPARE_LESS = -1,
     DS_COMPARE_EQUAL = 0,
     DS_COMPARE_GREATER = 1
} DS_Compare;

typedef struct {
     DS_Compare (*function)(const DS_Generic data1, const DS_Generic data2, DS_Generic user_data);
     DS_Generic user_data;
} DS_CompareCallback;

typedef struct {
     DS_Size (*function)(const DS_Generic data, DS_Size size, DS_Generic user_data);
     DS_Generic user_data;
} DS_HashCallback;

#endif