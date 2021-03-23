//test.c
//testing code for dataid

/** WORK IN PROGRESS */

#include<stdio.h>
#include<assert.h>

#include"dataid.h"

int main(void) {
	
	printf("==========testing dataid=============\n");
	printf("(If the program aborts, test fails...)\n");
	
	dinit(NULL);
	
	float* pi;
	char* song;
	const char* literal_song = "Twinkle twinkle little star\n"
	int d1, d2;
	
	pi = malloc(sizeof(float));
	assert(pi);
	
	song = malloc( (strlen(literal_song)+1) * sizeof(char) );
	assert(song);
	strcpy(song, literal_song);
	
	d1 = dset(pi)
	assert(dget(d1));
	assert(dget(d1)==pi);
	*(dget(d1)) = d1;
	assert(*dget(d1) == 3.14);
	
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