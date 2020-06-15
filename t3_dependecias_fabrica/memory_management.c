#include "memory_management.h"
#include<stdio.h>

void* allocate(size_t s){
	void * new = malloc(s);
	if(new == NULL){
		printf("Insuficiente Memory!!");
		exit(1);
	}
	return new;
}

void deallocate(void ** ptr){
	free(*ptr);
	(*ptr)=NULL;
}
