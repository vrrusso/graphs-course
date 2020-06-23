#ifndef LIST_H
#define LIST_H

#include "memory_management.h"
#define true 1
#define false 0

typedef struct route_{
    int destination;
    int time;
    int price;
}Route;


typedef int bool;
typedef struct list_ List;


List * create_list(size_t content_size);//!< creates the list based on the content_size
void erase_list(List ** ptr);

//!<  ***alwayss*** use item as a var in the client program
bool list_push_back(List* list,  void * item);
bool list_push_front(List* list, void * item);
bool list_insert(List* list, void * item,int index);
void * list_front(List * list);
void * list_back(List * list);

void list_pop_front(List * list);
void list_pop_back(List * list);


//!< uses you own print function based on data type
void list_print(List* list, void (*printer_function)(void *) );
void list_reverse_print(List* list,void (*printer_function)(void *));

//!< use your own equal function for the given data type
//!<it must return true(1) in case the items are the same or false(0) elsewhere
bool list_search(List * list,void * item, bool (*equal_function)(void *,void *));
void * list_remove(List * list, void * item, bool(*equal_function)(void *,void *));

int list_size(List * list);
bool list_empty(List * list);
Route * vectorize(List * list);
int list_size(List * list);

#endif
