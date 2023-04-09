# DynamicArray

An implementation of a dynamic array data structure in C. It supports fast insertion and dynamic memory allocation. It has support for other features in similar programs such as _find, _remove, etc. It has support for four data types : int, char, float and double. It's meant to be analogous to vectors in C++.

## Installation
Everything needed is contained in the included header file. Simply add this line to the top of your file and you should be good to go!

    #include"DynamicArray.h"
    
 You may also use the included .mk file to compile a small test program demonstrating the functions of the structure.
## How To Use
To start, call the _init() function and pass it the DataType of the array, a pointer to the initial data, and the size of the intial data. The function will take care of the rest for you.

    DynamicArray *intVector = DynamicArray(INT, intPtr, 5);

If done correctly, you should have a dynamic array containing your initial data and of the typing of your choosing.
From there, call the functions as needed, passing the pointer to your array. More information on the functions and their use can be found in the source code.

    DynamicArray_append(array, elemToAppendPtr);
    DynamicArray_find(array, elemToFindPtr);
    DynamicArray_get(array, index);
    DynamicArray_print(array);
As shown, you'll be using pointers quite a bit so make sure to call the provided delete function when you're done. Make sure you pass a reference to the pointer you've been working with. This will ensure that everything, including the pointer, is free'd and null'd safely!

	    //....
	    DynamicArray_delete(&array);
	    return 0;
    }



