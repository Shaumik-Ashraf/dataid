//test.c
//testing code for dataid

#include<stdio.h>
#include<assert.h>

#include"dataid.h"

int main(void) {
	
	printf("==========testing dataid=============\n");
	printf("(If the program aborts, test fails...)\n");
	
	printf("ptr size: %d\n",   sizeof(void*));
	printf("int size: %d\n",   sizeof(int));
	printf("uint size: %d\n",  sizeof(unsigned int));
	printf("long size: %d\n",  sizeof(long int));
	printf("ulong size: %d\n", sizeof(unsigned long int));
	printf("ull size: %d\n", sizeof(unsigned long long int));
	
/*
	dinit(void (*error_handler)(const char* error_msg));
	dset_capacity(size_t n, char immutable_flag);

	void dtrim_capacity();

	did_t dset(void* heapmem);

	did_t dclone(void* x, size_t n);

	void* dget(did_t d);

	void* dremove(did_t d);

	void dfree(did_t d);
*/
	
	printf("==========test success!!=============\n");
	
	return(0);
}