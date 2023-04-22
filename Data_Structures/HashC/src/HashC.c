/**
 * @file HashC.c
 * @author your name (you@domain.com)
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

#define DEFAULT_SIZE 100 //The default size of the table. Change this as needed

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

/**
 * @brief Our main hash function. Accepts a pair and runs its respective string through
 * the algorithm and returns an index for this pair.
 * 
 * @param pair 
 * @return unsigned int An index from 0 to whatever the max value is.
 */
static unsigned int HashC_hashcode(HashC_pair *pair, size_t max_size) {
    //Run pair's string through the algorithm, taking into account the 
    //maximum size for the table.
    unsigned int sum = 0;

    for (size_t i = 0; i < strlen(pair->key); i++) {
        sum += pair->key[i];
    }

    #ifdef DEBUG
        printf("The index for this key %s is %zu\n", pair->key, sum % max_size);
    #endif
    return sum % max_size;
}

void HashC_insert(HashC_table *table, const char *key, int value) {
    HashC_pair *pair = malloc(sizeof(HashC_pair));
    if(pair == NULL) {
        return;
    }

    pair->key = malloc(strlen(key) + 1);
    if(pair->key == NULL) {
        free(pair);
        return;
    }

    strcpy(pair->key, key);

    pair->value = value;

    table->table[HashC_hashcode(pair, table->max_size)] = pair;

    table->size++;
}

int HashC_search(const char *key) {
    int hashIndex = 
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
