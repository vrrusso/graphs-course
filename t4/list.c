#include "list.h"
#include<stdio.h>
#include<stdlib.h>
#define ERROR -100

typedef struct node_{
	void * content;
	struct node_ * next;
	struct node_ * prev;
}Node;

struct list_{
	Node * begin;
	Node * end;
	int size;
	size_t data_size;
};

List * create_list(size_t content_size){
	List * new = (List*)allocate(sizeof(List));
	new->begin=NULL;
	new->end=NULL;
	new->size=0;
	new->data_size=content_size;
	return new;
}

void erase_nodes(Node * begin){
	Node * aux=begin;
	while(begin !=NULL){
		begin=begin->next;
		deallocate((void*)&(aux->content));
		deallocate((void*)&aux);
		aux=begin;
	}
}

void erase_list(List ** ptr){
	erase_nodes((*ptr)->begin);
	deallocate((void *)ptr);
		ptr=NULL;
}

bool list_empty(List * list){
	if(list!=NULL)
		return list->size==0?true:false;
	return true;
}

Node * allocate_node(void * item, size_t data_size){
	Node * new = (Node *)allocate(sizeof(Node));
	new->content = allocate(data_size);
	//transfer the data from item to new->content byte to byte
	//TODO entender melhor
	int i;
    for (i=0; i<data_size; i++){
       	*(char *)(new->content + i) = *(char *)(item + i);	
	}
	return new;
}

bool list_push_back(List * list,void * item){
	if(list!=NULL){
		Node * new = allocate_node(item,list->data_size);	
		if(!list_empty(list))
			list->end->next = new;
		else
			list->begin = new;
		new->next=NULL;
		new->prev=list->end;
		list->end = new;
		list->size++;
		return true;
	}
	return false;
}

void * list_front(List * list){
	if(list != NULL && !list_empty(list))
		return list->begin->content;
	return NULL;
}

void * list_back(List * list){
	if(list != NULL && !list_empty(list))
		return list->end->content;
	return NULL;
}




void list_pop_front(List * list){
	if(list!=NULL && !list_empty(list)){
		Node * p = list->begin;
		list->begin=list->begin->next;
		if(p == list->end){
			list->end = NULL;	
		}
		else{	
			list->begin->prev=NULL;
		}
		deallocate(&(p->content));
		deallocate((void **)&p);
		list->size--;
	}
}


void list_pop_back(List * list){
	if(list!= NULL && !list_empty(list)){
		Node * p = list->end;
		list->end = list->end->prev;
		if(p == list->begin){
			list->begin = NULL;
		}
		else
			list->end->next = NULL;
		deallocate(&(p->content));
		deallocate((void **)&p);
		list->size--;
	}
}


bool list_push_front(List * list, void * item){
	if(list!=NULL){
		Node * new = allocate_node(item,list->data_size);
		if(!list_empty(list)){
			new->next = list->begin;
			list->begin->prev=new;
		}
		else{
			list->end=new;		
			new->next=NULL;
		}
		new->prev=NULL;
		list->begin = new;
		list->size++;
		return true;
	}
	return false;
}

bool list_insert(List* list,void * item,int index){
	return true;
}

void list_print(List* list, void (*printer_function)(void *)){
	if(list != NULL && !list_empty(list)){
		Node * aux = list->begin;
		while(aux != NULL){
			(*printer_function)(aux->content);
			printf(" ");
			aux=aux->next;
		}

	}
	printf("\n");
	//printf("Non initialized or empty listy!\n");
}

void list_reverse_print(List* list, void (*printer_function)(void *)){
	if(list !=NULL && !list_empty(list)){
		Node * aux = list->end;
		while(aux != NULL){
			(*printer_function)(aux->content);
			aux=aux->prev;
		}
		printf("\n");
		return;
	}
	printf("Non initialized or empty listy!\n");
}

bool list_search(List * list,void * item, bool (*equal_function)(void *,void *)){
	if(list!=NULL && !list_empty(list)){
		Node * p = list->begin;
		while(p!=NULL){
			if((*equal_function)(item,p->content))
				return true;
			p=p->next;
		}
	}
	return false;
}

void * list_remove(List * list, void * item, bool(*equal_function)(void *,void *)){
	if(list !=NULL && !list_empty(list)){
		Node * p = list->begin;
		while(p!=NULL){
			if((*equal_function)(item,p->content)){
				if(p == list->begin)
					list->begin = p->next;
				else
					p->prev->next=p->next;
				if(p == list->end)
					list->end=p->prev;
				else
					p->next->prev=p->prev;
				void * val = p->content;
				p->next = NULL;
				p->prev = NULL;
				deallocate((void**)&(p));
				list->size--;
				return val;
			}
			p=p->next;
		}
	}
	return NULL;
}


Route * vectorize(List * list){
	Node * p = list->begin;
	Route * vector = (Route *)malloc(sizeof(Route)*list->size);
	for(int i=0;i<list->size;i++){
		vector[i].destination = ((Route*)p->content)->destination;
		vector[i].time = ((Route*)p->content)->time;
		vector[i].price = ((Route*)p->content)->price;
		p=p->next;
	}
	return vector;
}

int list_size(List * list){
	return list->size;
}