#ifndef DATA_STRUCTURES_STRING_H
#define DATA_STRUCTURES_STRING_H

#include "data-structures.h"

typedef struct String * String;

struct String {
     DS_UInt8 *string;
     DS_Size size;
     DS_Size capacity;
};

DATA_STRUCTURES_API
String String_Create(const DS_UInt8 *string);

DATA_STRUCTURES_API
DS_Void String_Destroy(String string);

DATA_STRUCTURES_API
DS_Size String_GetLength(const String string);

DATA_STRUCTURES_API
DS_Size String_GetCapacity(const String string);

#endif