//example.c
//example code for dataid

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"dataid.h"


//allocate string function; not everyone has strdup()
static void* str(const char* s) {
	size_t len = strlen(s)+1;
	void* ret = malloc(len);
	
	memcpy(ret, s, len);
	return(ret);
}


int main(void) {
	
	int map[3][2]; //map where [i][0] is key, [i][1] is value
	int i;
	
	
	//intialize dataid system
	dinit(NULL);
	
	
	//set initialized values into dataid system, while assigning them to map
	map[0][0] = dset(str("red"));
	map[0][1] = dset(str("apple"));
	
	map[1][0] = dset(str("yellow"));
	map[1][1] = dset(str("banana"));

	map[2][0] = dset(str("blue"));
	map[2][1] = dset(str("blueberry"));
	
	
	//get values to print them
	for(i=0; i<3; i++) {
		printf("%s => %s\n", dget(map[i][0]), dget(map[i][0]));
	}
	
	
	//dataid automatically free's memory on return;
	return(0);
}