# bstC
An implementation of a binary search tree in C using integers as the keys.

## Installation
Simply include the associated header file and ensure your build system points to the header and source file when 
compiling.
```
#include"bstC.h"
```
## How to Use
You'll need to initialize a pointer to the main tree struct *BstC* using the init() function.
```
BstC *bst = BstCNode_init(void);
```
The function will either return a valid pointer to a BstC struct or NULL if an error occurs.
From there, use the included functions as needed, making sure to use the delete function when you finish 
with the tree.
```
BstCNode_delete(&bst);
```
More information can be found in the include header file on how the functions work.
