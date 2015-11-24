
#include <stdio.h>
#include <stdlib.h>

#include "slist.h"

void
sllist_init(SLList * list)
{
	list->head = NULL;
}

// Add int value to the end of list. The values may be repeated.
void
sllist_add_end( SLList *list, int value )  {
	SLEntry * e = list->head;
	SLEntry * last = e;
	SLEntry * new = (SLEntry *) malloc(sizeof(SLEntry));
	new -> value = value;
	new -> next = NULL;
	if(last == NULL){
		list->head = new;
		return;
	}
	e = last -> next;
	while(e!= NULL){
		last = e;
		e = last ->next;
	}
	last -> next = new;

}


// Remove first occurrence of value in the list. It returns 1 if value is found or 0 otherwise.
int sllist_remove(SLList *list, int value) {
	SLEntry * e = list->head;
	SLEntry * last = e;
	if(last == NULL)
		return 0;
	e = last -> next;
	if(last -> value == value){
		list ->head = last->next;
		return 1;
	}
	while(e!= NULL){
		if(e->value == value){
			last->next = e -> next;
			return 1;
		}
		last = e;
		e = last -> next;
	}
	return 0;
}


// Removes from the list and frees the nodes of all the items that are min <= value <= max
void sllist_remove_interval(SLList *list, int min, int max) {
	SLEntry *e = list->head;
	SLEntry * last = e;
	if(last == NULL)
		return;
	e = last -> next;
	while(last->value >= min && last -> value <= max) {
		list ->head = last->next;
		free(last);
		last = list->head;
		e = last -> next;
	}
	while(e!= NULL){
		if(e->value >= min && e->value <= max){
			last->next = e->next;
			//printf("%d\n", e->value );
			//printf("%d\n", e->next->value);
			free(e);
		}
		last = e;
		e = last -> next;
	}
}


// It allocates and returns a new list with the intersection of the two lists, that is the 
// list of all the items that are common to the two lists. The items in the intersection are
// unique. 
SLList *
sllist_intersection(SLList *a, SLList *b) {
	SLList l;
	SLList * list = &l;
	sllist_init(list);
	SLEntry * e = a -> head;
	list -> head = NULL;
	while(e!= NULL){
		sllist_remove(list,e->value);
		if(sllist_remove(b,e->value)){
			sllist_add_end(list,e->value);
			sllist_add_end(b,e->value);
		}
		e = e -> next;
		//printf("%s\n", e->value );
	}
	return list;
}

void
sllist_print(SLList *list)
{
	// Move to the end
	SLEntry * e = list->head;

	printf("--- List ---\n");
	while (e!= NULL) {
		printf("val=%d\n", e->value);
		e = e->next;
	}
}

