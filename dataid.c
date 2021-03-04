//dataid.c

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<limits.h>
#include<assert.h>

#include"dataid.h"


//static globals
static struct {
	size_t length;
	size_t capacity;
	unsigned long long* array;
} chain;

static void (*error_f)(const char*);
static size_t init_capacity;
static char immutable;


//static functions
static void default_error(const char* msg) {	
	fprintf(stderr, "data id error: %s\n", msg);
	exit(1);
}

//special assert for dataid library
//c -> condition; error handler only called if c is true
//e -> errno or 0
//s -> error message prefix if errno, or full error message
static void dassert(int c, int e, const char* s) {
	static char buffer[128];
	if( (!c) && e ) { 
		snprintf(buffer, 128, "%s: %s", s, strerror(e));
		error_f(buffer);
	}
	else if( !c ) {
		error_f(s);
	}
}

static void destroy_chain() {
	size_t i;
	
	for(i=0; i<chain.length; i++) {
		if( chain.array[i] ) {
			free( (void*)chain.array[i] );
		}
	}
	free(chain.array);
}

static void resize_chain() {
	dassert( !immutable, 0, "data id array has reached set capacity" );
	
	void* tmp;
	chain.capacity *= 2;
	tmp = realloc(chain.array, chain.capacity);
	dassert( tmp != NULL, errno, "realloc" );
	chain.array = tmp;
}


//library functions
void dinit(void (*error_handler)(const char*)) {
	error_f = error_handler ? error_handler : default_error;
	dassert(1,0,NULL); //make sure static buffer is initialized
	
	chain.length = 0;
	chain.capacity = init_capacity;
	dassert(chain.capacity != 0, 0, "dinit(): initial capacity cannot be 0");
	chain.array = (unsigned long long*)malloc(chain.capacity * sizeof(unsigned long long));
	dassert(chain.array != NULL, errno, "malloc()");
	
	atexit(destroy_chain);
}

void dset_capacity(size_t n, char immutable_flag) {
	immutable = immutable_flag;
	init_capacity = n;
}

void dtrim_capacity() {
	dassert( !immutable, 0, "cannot trim immutable capacity" );
	void* tmp = realloc(chain.array, chain.length);
	dassert( tmp != NULL, errno, "realloc()" );
	chain.array = tmp;
}

did_t dset(void* heapmem) {
	if( chain.length == chain.capacity ) {
		resize_chain();
	}
	chain.array[ chain.length++ ] = (unsigned long long)heapmem;
	dassert( chain.length < INT_MAX, 0, "maximum int value has been reached" );
	return( (did_t)(chain.length - 1) );
}

did_t dclone(void* x, size_t n) {
	void* y = malloc(n);
	dassert(y != NULL, errno, "malloc()");
	memcpy(y, x, n);
	return( dset(y) );
}

void* dget(did_t d) {
	dassert( (d < chain.length) && (d >= 0), 0, "invalid data id" );
	dassert( chain.array[d] != 0ULL, 0, "data was removed" );
	return( (void*)chain.array[d] );
}

void* dremove(did_t d) {
	void* ret = dget(d);
	chain.array[d] = 0ULL;
	return(ret);
}

void dfree(did_t d) {
	free( dremove(d) );
}