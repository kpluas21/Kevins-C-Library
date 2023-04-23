/**
 * @file HashC.c
 * @author Kevin Pluas (kpluas21@gmail.com)
 * @brief Implementation for hashmaps in C
 * @version 0.1
 * @date 2023-04-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"HashC.h"

#define DEFAULT_SIZE 300 //The default size of the table. Change this as needed

/**
 * @brief Initializes a key-value pair for storage. The user should not have to call
 * this function.
 * 
 * @param key Our string key
 * @param value The value associated with the string key
 * @return HashC_pair* NULL if error encountered.
 */
static unsigned int HashC_hashcode(const char *key);
static HashC_pair *HashC_pair_init(const char *key, int value);

HashC_table *HashC_init(void) {
    HashC_table *table = malloc(sizeof(HashC_table));
    if(table == NULL) {
        return NULL;
    }
    table->table = malloc(sizeof(HashC_pair) * DEFAULT_SIZE);

    if(table->table == NULL) {
        free(table);
        return NULL;
    }

    for(size_t i = 0; i < DEFAULT_SIZE; i++) {
        table->table[i] = NULL;
    }
    table->max_size = DEFAULT_SIZE; 
    table->size = 0;

    return table;
}

static unsigned int HashC_hashcode(const char *key) {
    //Run pair's string through the algorithm, taking into account the 
    //maximum size for the table.
    unsigned int sum = 0;

    for (size_t i = 0; i < strlen(key); i++) {
        sum += key[i];
    }

    #ifdef DEBUG
        printf("The index for this key %s is %d\n", key, sum % DEFAULT_SIZE);
    #endif
    return sum % DEFAULT_SIZE;
}

static HashC_pair *HashC_pair_init(const char *key, int value) {
    HashC_pair *pair = malloc(sizeof(HashC_pair));
    if(pair == NULL) {
        return NULL;
    }
    pair->key = malloc(strlen(key) + 1);
    if(pair->key == NULL) {
        free(pair);
        return NULL;
    }
    pair->key[sizeof(key)] = '\0';
    strcpy(pair->key, key);
    pair->value = value;

    return pair;
}

void HashC_insert(HashC_table *table, const char *key, int value) {
    int hashIndex = HashC_hashcode(key);

    if(table->size == table->max_size) {
        printf("Error: Max number of pairs reached for this table!\n");
        return;
    }

    HashC_pair *pair = HashC_pair_init(key, value);
    if(pair == NULL) {
        printf("Error: cannot allocate memory for hashC pair\n");
        return;
    }

    if( (table->table[hashIndex] != NULL) && 
        strcmp(table->table[hashIndex]->key, pair->key) == 0) {

        printf("Error: Duplicate key %s already in table\n", key);
        free(pair);
        return;
    }

    //Start open probing for an empty spot on the table
    while(table->table[hashIndex] != NULL) {
        hashIndex++;
        hashIndex %= table->max_size;
    }
    table->table[hashIndex] = pair;

    table->size++;
}

int HashC_search(HashC_table *table, const char *key) {
    unsigned int hashIndex = HashC_hashcode(key);

    if(table->table[hashIndex] != NULL && 
        strcmp(table->table[hashIndex]->key, key) == 0) {

        return table->table[hashIndex]->value;
    }
    
    return -1;
}

void HashC_delete(HashC_table **table) {
    if(table == NULL || (*table) == NULL) {
        return;
    }
    for (size_t i = 0; i < (*table)->max_size; i++) {
        if((*table)->table[i] != NULL) {
            free((*table)->table[i]);
        }
    }
    free((*table)->table);
    free((*table));
    (*table) = NULL;

}

size_t HashC_table_size(HashC_table *table) {
    return table->size;
}
