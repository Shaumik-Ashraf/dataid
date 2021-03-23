# dataid

A data handle system that simplifies using advanced C structures. Possibly also known as a pointer table or vertex array.

The dataid system stores dynamically allocated memory
in a hidden array and returns did_t handler, which is
the int index to the array. This allows you to manipulate
void*s more simply, and by implementing advanced data
structues for int, you can expand their use to any 
structure. The dataid system also implements automatic
garbage collection, bounds checking, and error handling 
customization.
 
Built on C99 and is cross platform (well, as X-platform as C99).

## Usage
 - Download this repository
 - Add `dataid.c` and `dataid.h` to your workspace directory
 - Create the object file dataid.o, ie: `gcc -c dataid.o`
 - Include the header file in your code, ie:
```c 
#include"dataid.h"

int main(void) {
	//... your code ...
```
 - Compile, ie: `gcc -o main.exe main.c dataid.o`

**See example.c for example code**

## Documentation
```c
//initializes dataid system
void dinit(void (*error_handler)(const char* error_msg));
```

```c
//specify the capacity for dataid system
void dset_capacity(size_t n, char immutable_flag);
```

```c
//minimize the memory allocated to dataid system 
void dtrim_capacity();
```

```c
//enter dynamically allocated (malloc/calloc/realloc) memory to dataid system
did_t dset(void* heapmem);
```

```c
//allocate n bytes and copy over x; add the copy to dataid system
did_t dclone(void* x, size_t n);
```

```c
//get memory pointer from data id handle
void* dget(did_t d);
```

```c
//removes data from dataid system (it will NOT be free'd and dget() will no longer work on it)
void* dremove(did_t d);
```

```c
//removes and frees the data from dataid system
void dfree(did_t d);
```

**See dataid.h for more indepth documentation**

## Todo
 - maybe create a `did_t dmalloc(size_t bytes)` function
 - add test code, examples code, and makefile
 - add wake
 - add doxygen

## Contributors
Shaumik Ashraf

## License
This project is under the MIT LICENSE.
