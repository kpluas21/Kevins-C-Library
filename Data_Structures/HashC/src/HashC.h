#ifndef HASHC_H
#define HASHC_H

/**
 * @file HashC.h
 * @author Kevin Pluas (kpluas21@gmail.com)
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
 * @brief The main key-value pair data unit of our hash table.
 * 
 * @var HashC_pair::key
 * A string which serves as the key to look up the value
 * 
 * @var HashC_pair::value
 * The main value stored in the hash tables indices
 * 
 */
typedef struct HashC_pair {
    char *key;
    int value;
}HashC_pair;

/**
 * @brief The main hash table object which contains our pairs. This is the main
 * object that users will interact with.
 * 
 * @var HashC_table::max_size
 * The maximum amount of key-value pairs allowed in the hash table. The default is 300 and this can be changed
 * by modifying the DEFAULT_SIZE variable.
 * 
 * @var HashC_table::size
 * The amount of key-value pairs currently in the table
 * 
 * @var HashC_table::table
 * Pointer to a pointer of a HashC_pair object, in other words, it's a pointer to an array of HashC_pairs.
 * 
 */
typedef struct HashC_table {
    size_t max_size; 
    size_t size;
    HashC_pair **table;
}HashC_table;

/**
 * @brief Initializes and returns a pointer to a new hash table. The maximum number
 * of pairs allowed is defined in the .c file and can be changed as needed. The current 
 * default is 100.
 * 
 * @return A pointer to a valid HashC_table object, NULL otherwise.
 */
HashC_table *HashC_init(void);

/**
 * @brief Attempts to insert a key-value pair into the hash table. This table uses
 * open probing to avoid collisions.
 * 
 * @param table A pointer to a valid HashC_table object.
 * @param key A string key
 * @param value The value associated with the string key
 */
void HashC_insert(HashC_table *table, const char *key, int value);

/**
 * @brief Attempts to search for the key provided in the table and returns the 
 * associated value
 * @return The integer value associated with the string key.
 */
int HashC_search(HashC_table *table, const char *key);

/**
 * @brief Deletes and frees up any memory associated with the hash table provided
 * 
 * @param table A pointer to a valid HashC_table pointer. 
 */
void HashC_delete(HashC_table **table);

/**
 * @brief Returns the current number of key-value pairs stored in the table
 * 
 * @param table A pointer to a valid HashC_table object.
 * @return The number of key-value pairs in the table
 */
size_t HashC_table_size(HashC_table *table);

#endif //_HASH_C