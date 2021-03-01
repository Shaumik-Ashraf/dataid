//dataid.h 
/* The dataid system stores dynamically allocated memory
 * in a hidden array and returns did_t handler, which is
 * the int index to the array. This allows you to manipulate
 * void*s more simply, and by implementing advanced data
 * structues for int, you can expand their use to any 
 * structure. The dataid system also implements automatic
 * garbage collection, bounds checking, and error handling 
 * customization.
 * 
 * Built on C99 and is cross platform (well, as X-platform as C99)
 */


#ifndef _DATAID_H_
#define _DATAID_H_

//data id type
typedef int did_t; 


//initializes dataid system
//NOTE: uses atexit() to free and destroy dataid system
//@param error_handler - use this to implement your own error handling 
//		mechanism if set to NULL, a default error handler is used that 
//		prints the error message to stderr and exits the program with 1
void dinit(void (*error_handler)(const char* error_msg));


//specify the capacity for dataid system
//IF THIS FUNCTION IS CALLED, IT MUST BE BEFORE dinit()
//@param n - maximum number of pointers to store in dataid system
//		by default, if this value is exceeded, the system will reallocate
//@param immutable_flag - if this value is set to true, dataid system will
//		call error handler, which by default exits the program.
//NOTE: the array is still allocated on heap regardless of immutable_flag
//NOTE: if the error handler doesn't exit, the dataid array will still reallocate
//		this feature is intended for optimization without crashing the code
void dset_capacity(size_t n, char immutable_flag);


//minimize the memory allocated to dataid system 
void dtrim_capacity();


//enter dynamically allocated (malloc/calloc/realloc) memory to dataid system
//NOTE: you may enter automatic/stack memory as long as you call dremove() 
//		on its handle later, OR you know that free() behaves "well" on stack memory
//		(in my experience the behavior of free on stack memory is undefined and sus)
//@param heapmem - pointer to dynamically allocated memory (returned from malloc/calloc/realloc)
//@return - data id handle
did_t dset(void* heapmem);


//allocate n bytes and copy over x; add the copy to dataid system
//@param x - pointer to copy, may be heap or stack memory
//@param n - bytes to allocate (and copy) for clone
//@return - data id handle of copy
//NOTE: by making n a string length or array size, your can add strings/arrays to dataid system
did_t dclone(void* x, size_t n);


//get memory pointer from data id handle
//@param d - data id
//@return - data corresponding to data id from dset() or dclone()
void* dget(did_t d);


//removes data from dataid system (it WILL not be free'd and dget() will no longer work on it)
//@param d - data id to remove
//@return - data removed, which you must now handle
void* dremove(did_t d);


//removes and frees the data from dataid system
//@param d - data id to free
void dfree(did_t d);

#endif