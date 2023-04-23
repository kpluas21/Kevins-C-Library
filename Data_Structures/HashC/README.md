# HashC
My implementation of a hash table in C. This data structures stores key-value pairs in an array for very fast insertion and searching. 
HashC is not generic unfortunately, so it uses string keys and int values. However I'm sure with a little finesse it can handle any data types.

## Installation
Simply include the header file and make sure your build system points to the header and source file. 
```
#include"HashC.h"
```

## How to Use
To start using the hash table, you'll need to initialize a pointer to the HashC_table struct like so 
```
HashC_table *hash_table = HashC_init();
```
It will either return a valid pointer to a HashC table or NULL if anything goes wrong. 
The default size is 300 key-value pairs however that can be changed easily by simply changing the constant in the source file
```
#define DEFAULT_SIZE 300
```
From there, simply call the functions as needed. More information can be found in the header file as they are rather straight-forward.
