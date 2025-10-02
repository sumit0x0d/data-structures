#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <hash-table.h>

#include <hash-table-pair.h>

struct hash_table {
    HashTablePair *pair;
    DS_Size key_size;
    DS_Size value_size;
    DS_Size bucket_count;
    DS_CallbackHash hash_callback;
    DS_Generic hash_context;
    DS_CallbackCompare compare_callback;
    DS_Generic compare_context;
};

HashTable HashTable_Create(DS_Size key_size, DS_Size value_size, DS_Size bucket_count, DS_CallbackHash hash_callback,
    DS_Generic hash_context, DS_CallbackCompare compare_callback, DS_Generic compare_context)
{
    HashTable table = (HashTable)malloc(sizeof (struct hash_table));
    if (!table) {
        return NULL;
    }
    table->pair = (HashTablePair *)calloc(bucket_count, sizeof (struct hash_table_pair));
    if (!table->pair) {
        free(table);
        return NULL;
    }
    table->key_size = key_size;
    table->value_size = value_size;
    table->bucket_count = bucket_count;
    table->hash_callback = hash_callback;
    table->compare_context = hash_context;
    table->compare_callback = compare_callback;
    table->compare_context = compare_context;
    return table;
}

DS_Void HashTable_Destroy(HashTable table)
{
    for (DS_Size i = 0; i < table->bucket_count; i++) {
        if (table->pair[i]) {
            HashTablePair_Destroy(table->pair[i]);
        }
    }
    free(table);
}

DS_Generic HashTable_GetKey(HashTablePair pair)
{
    return pair->key;
}

DS_Generic HashTable_GetValue(HashTablePair pair)
{
    return pair->value;
}

DS_Void HashTable_Insert(HashTable table, const DS_Void *key, const DS_Void *value)
{
    DS_Size index = table->hash_callback(key, table->bucket_count, table->hash_context);
    if (!table->pair[index]) {
        table->pair[index] = HashTablePair_Create(key, table->key_size, value, table->value_size);
        return;
    }
    DS_Compare compare = DS_COMPARE_EQUAL;
    HashTablePair pair = table->pair[index];
    do {
        compare = table->compare_callback(key, pair->key, table->compare_context);
        if (compare) {
            pair = pair->next;
        } else {
            memcpy(table->pair[index]->value, value, table->value_size);
            return;
        } 
    } while (compare && pair->next);
    pair->next = HashTablePair_Create(key, table->key_size, value, table->value_size);
}

DS_Void HashTable_Remove(HashTable table, const DS_Void *key)
{
    DS_Size index = table->hash_callback(key, table->bucket_count, table->hash_context);
    if (table->pair[index]) {
        int compare = 0;
        HashTablePair pair = table->pair[index];
        HashTablePair ppair = pair;
        do {
            compare = table->compare_callback(key, pair->key, table->compare_context);
            if (compare) {
                ppair = pair;
                pair = pair->next;
            } else {
                ppair->next = pair->next;
                HashTablePair_Destroy(pair->next);
                pair = NULL;
            }
        } while (compare && pair->next);
    };
}

HashTablePair HashTable_Search(HashTable table, const DS_Void *key)
{
    DS_Size index = table->hash_callback(key, table->bucket_count, table->hash_context);
    if (table->pair[index]) {
        DS_Compare compare = 0;
        HashTablePair pair = table->pair[index];
        do {
            compare = table->compare_callback(key, pair->key, table->compare_context);
            if (compare) {
                pair = pair->next;
            } else {
                return pair;
            }
        } while (compare != DS_COMPARE_EQUAL && pair);
    }
    return NULL;
}
