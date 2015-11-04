
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LinkedList.h"

//
// Initialize a linked list
//
void llist_init(LinkedList * list)
{
	list->head = NULL;
}

//
// It prints the elements in the list in the form:
// 4, 6, 2, 3, 8,7
//
void llist_print(LinkedList * list) {
	
	ListNodeLink * e;

	if (list->head == NULL) {
		printf("{EMPTY}\n");
		return;
	}

	printf("{");

	e = list->head;
	while (e != NULL) {
		printf("%s", e->value);
		e = e->next;
		if (e!=NULL) {
			printf(", ");
		}
	}
	printf("}\n");
}

//
// Appends a new node with this value at the beginning of the list
//
void llist_add(LinkedList * list, char * value) {
	// Create new node
	ListNodeLink * n = (ListNodeLink *) malloc(sizeof(ListNodeLink));
	n->value = value;
	
	// Add at the beginning of the list
	n->next = list->head;
	list->head = n;
}

//
// Returns true if the value exists in the list.
//
int llist_exists(LinkedList * list, char * value) {
	ListNodeLink * e = list->head;
	while (e != NULL) {
		if (!strcmp(e->value,value)){
			return 1;
		}
		e = e->next;
	}
	return 0;
}

//
// It removes the entry with that value in the list.
//
int llist_remove(LinkedList * list, char *  value) {
	ListNodeLink * e = list->head;
	if(e != NULL && !strcmp(e->value,value)){
		list->head = e->next;
		free(e);
		e = list->head;
		return 1;
	}

	while (e != NULL && e->next!=NULL) {
		if (!strcmp(e->next->value,value)){
			e->next = e->next->next;
			return 1;
		}
		e = e->next;
	}
	return 0;
}

//
// It stores in *value the value that correspond to the ith entry.
// It returns 1 if success or 0 if there is no ith entry.
//
int llist_get_ith(LinkedList * list, int ith, char ** value) {
	int count = 1;
	ListNodeLink * e = list->head;
	while (e != NULL) {
		//e = e->next;
		if (count == ith){
			*value = (e->value);
			return 1;
		}
		e = e->next;
		count++;
	}
	return 0;
}

//
// It removes the ith entry from the list.
// It returns 1 if success or 0 if there is no ith entry.
//
int llist_remove_ith(LinkedList * list, int ith) {
	int count = 2;
	ListNodeLink * e = list->head;
	while (e != NULL) {
		e = e->next;
		if (count == ith){
			e->next = e->next->next;
			return 1;
		}
		count++;
	}
	return 0;
}

//
// It returns the number of elements in the list.
//
int llist_number_elements(LinkedList * list) {
	int count = 0;
	ListNodeLink * e = list->head;
	while (e != NULL) {
		e = e->next;
		count++;
	}
	return count;
}


//
// It saves the list in a file called file_name. The format of the
// file is as follows:
//
// value1\n
// value2\n
// ...
//
int llist_save(LinkedList * list, char * file_name) {
	FILE * file = fopen(file_name,"wb");
	if(file == NULL)
		return 0;
	ListNodeLink * e;
	e = list->head;
	while (e != NULL) {
		fprintf(file, "%s\n", e->value);
		e = e->next;
	}
	fclose(file);
	return 0;
}

//
// It reads the list from the file_name indicated. If the list already has entries, 
// it will clear the entries.
//
int llist_read(LinkedList * list, char * file_name) {
	FILE * file = fopen(file_name,"r");
	if(file == NULL)
		return 0;
	//char * number = malloc(20*sizeof(char));
	char * number;
	if(list->head != NULL){
		llist_clear(list);
	}
	
	while((fscanf(file, "%s", number)) != EOF) {
		//print(number);
		llist_add(list , number);
	}
	fclose(file);
	return 1;
}


//
// It sorts the list. The parameter ascending determines if the
// order is ascending (1) or descending(0).
//
void llist_sort(LinkedList * list, int ascending) {
	ListNodeLink * p = list->head;
	ListNodeLink * pend = NULL;
	char * temp;
	if(p == NULL) {
		return;
	}
	if(ascending == 1){
		for(;p->next != NULL;p = p->next){
			//printf("1\n");
			pend = p->next;
			while(pend != NULL){
				if(strcmp(pend->value,p->value)< 0){
				//	printf("3");
					temp = p->value;
					p->value = pend->value;
					pend->value = temp;
				}
			//	printf("%d",pend->value);
			pend = pend->next;
			}
		}
	}
	else if(ascending == 0){
		for(;p->next != NULL;p = p->next){
			pend = p->next;
			while(pend != NULL){
				if(strcmp(pend->value,p->value)> 0){
				//	printf("3");
					temp = p->value;
					p->value = pend->value;
					pend->value = temp;
			}
			//printf("%d",pend->value);
			pend = pend->next;
			}
		}
	}
}



//
// It removes the first entry in the list and puts value in *value.
// It also frees memory allocated for the node
//
int llist_remove_first(LinkedList * list, char * value) {
	ListNodeLink * e = list->head;
	if(e!=NULL){
		*value = *(e->value);
		list->head = e->next;
		free(e);
		return 1;
	}
	return 0;
}

//
// It removes the last entry in the list and puts value in *value/
// It also frees memory allocated for node.
//
int llist_remove_last(LinkedList * list, char *value) {
	ListNodeLink * e = list->head;
	while (e != NULL) {
		if(e->next->next == NULL){
			*value = *(e->next->value);
			free(e->next);
			e->next = NULL;
			return 1;
		}
		e = e->next;
		//free(e);
		//count++;
	}
  return 0;
}

//
// Insert a value at the beginning of the list.
// There is no check if the value exists. The entry is added
// at the beginning of the list.
//
void llist_insert_first(LinkedList * list, char * value) {
	ListNodeLink * n = (ListNodeLink *) malloc(sizeof(ListNodeLink));
	n->value = value;
	
	// Add at the beginning of the list
	n->next = list->head;
	list->head = n;
}

//
// Insert a value at the end of the list.
// There is no check if the name already exists. The entry is added
// at the end of the list.
//
void llist_insert_last(LinkedList * list, char * value) {
	ListNodeLink * e = list->head;
	ListNodeLink * n = (ListNodeLink *) malloc(sizeof(ListNodeLink));
	n->value = value;
	n->next = NULL;
	if(e == NULL) {
		list->head = n;
		return;
	}
	while (e->next != NULL) {
		e = e->next;
	}
	e->next = n;
}

//
// Clear all elements in the list and free the nodes
//
void llist_clear(LinkedList *list)
{
	//int count = 0;
	ListNodeLink * e = list->head;
	while (e != NULL) {
		e = e->next;
		free(e);
		//count++;
	}
	list->head = NULL;
	//return count;
}
