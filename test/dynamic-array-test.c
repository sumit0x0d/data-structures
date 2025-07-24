#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <dynamic-array.h>

// static int _compare_int(const void *data1, const void *data2);

int main()
{
     srand((int)time(NULL));
     struct dynamic_array *dArray = DynamicArray_Create(sizeof (int), 20, 1.5);
     int x = 2;
     DynamicArray_PushBack(dArray, &x);
     printf("%zu", DynamicArray_GetSize(dArray));
     return 0;
}

// static int _compare_int(const void *data1, const void *data2)
// {
//      if (*(int *)data1 < *(int *)data2) {
//           return -1;
//      }
//      if (*(int *)data1 > *(int *)data2) {
//           return 1;
//      }
//      return 0;
// }
