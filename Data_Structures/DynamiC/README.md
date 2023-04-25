# DynamiC

An implementation of a generic dynamic array data structure in C. It supports fast insertion and dynamic memory allocation. It can support any type with a clearly defined size in bytes.  

## Installation
Everything needed is contained in the included header and source file. Simply add this line to the top of your file and you should be good to go!

    #include"DynamiC.h"
    
You can also use the following command to try out the library!
```
make all 
```
This will create an executable that tests all of the functions and ensure they work on your machine.

## How To Use
To start, call the _init() function and pass it the array(or pointer) containing your inital data, the size(in bytes) of each element and the number of elements pointed to by the initial pointer.

        DynamiC *intVector = DynamiC(voidPtrToInitialData, sizeOfOneElem, numOfElems);

If done correctly, you should have a pointer to a dynamic array containing your initial data and of the typing of your choosing.
From there, call the functions as needed, passing the pointer to your array. More information on the functions and their use can be found in the source code.

        DynamiC_append(array, &elem);
        DynamiC_get(array, index);
Casting to the appropriate data type is a must when using certain functions such as _get. It is up to you to ensure the types match. For example :

```
//Retrieve an int at index 5 of our array
//Because _get returns void, we will need to cast to an int and dereference.

    int num;
    num = *(int*)DynamiC_get(intVector, 5);

```

As shown, you'll be using pointers quite a bit so make sure to call the provided delete function when you're done. Make sure you pass a reference to the pointer you've been working with. This will ensure that everything, including the pointer, is free'd and null'd safely!

	    //....
	    DynamiC_delete(&array);
        //array will be NULL at this point. 
	    return 0;
    }



