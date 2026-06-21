#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <hash-table.h>

static void _UnaryPrint(void *data, void *user_data);

int main(void)
{
   HashTable *obj;
   int i, value;
   HashTableUnaryCallback unary_callback;
   HashTableHashCallback hash_callback;

   srand((int)time(NULL));
   unary_callback.function = _UnaryPrint;
   unary_callback.user_data = NULL;

   obj = HashTable_Create(sizeof(int), 100, hash_callback);
   if (!obj) {
      fprintf(stderr, "HashTable_Create() failed\n");
      return 1;
   }
   printf("HashTable_Create() passed\n");

   for (i = 0; i < 10; i++) {
      value = rand() % 100;
      HashTable_Insert(htable, &value);
   }
   printf("HashTable_Insert() passed\n");
   HashTable_Traverse(htable, unary_callback);
   printf("\nHashTable_Traverse() passed\n");
   HashTable_Destroy(htable);
   printf("HashTable_Destroy() passed\n");
   printf("All hash-table tests passed!\n");

   return 0;
}

static void _UnaryPrint(void *data, void *user_data)
{
   (void)user_data;
   printf("%d ", *(int *)data);
}
