#ifndef _HASHC_H
#define _HASHC_H

/**
 * @file HashC.h
 * @author your name (you@domain.com)
 * @brief Interface for HashC.c
 * @version 0.1
 * @date 2023-04-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

typedef struct HashC HashC;
typedef struct HashC_pair HashC_pair;

/**
 * @brief Our table will be made out of pairs which is our main data unit.
 * Contains a string as its key and an int as the actual value
 * 
 */
typedef struct HashC_pair {
    char *key;
    int value;
}HashC_pair;

/**
 * @brief Our main table struct which contains our pairs. This is the main
 * object that users will interact with.
 * 
 */
typedef struct HashC_table {
    size_t max_size; //The maximum amount of pairs allowed in the table
    size_t size; //The amount of pairs currently in the table
    HashC_pair **table;
}HashC_table;

/**
 * @brief Initializes and returns a pointer to a new hash table. The maximum number
 * of pairs allowed is defined in the .c file and can be changed as needed. The current 
 * default is 100.
 * 
 * @return HashC_table* 
 */
HashC_table *HashC_init(void);

/**
 * @brief Attempts to insert a key-value pair into the hash table. This table uses
 * open probing to avoid collisions.
 * 
 * @param table 
 * @param key A string key
 * @param value The value associated with the string key
 */
void HashC_insert(HashC_table *table, const char *key, int value);

/**
 * @brief Attempts to search for the key provided in the table and returns the 
 * associated value
 * @return int
 */
int HashC_search(HashC_table *table, const char *key);

/**
 * @brief Deletes and frees up any memory associated with the hash table provided
 * 
 * @param table 
 */
void HashC_delete(HashC_table **table);

/**
 * @brief Returns the current number of key-value pairs stored in the table
 * 
 * @param table 
 * @return size_t 
 */
size_t HashC_table_size(HashC_table *table);

#endif //_HASH_C