typedef struct SLListEntry {
    char * name;
    char * value;
    struct SLListEntry * next;
} SLListEntry;

typedef struct SLList {
   SLListEntry * head;
} SLList;

SLList.c

#include "SLList.h"

// Create a single-linked list
SLList * sllist_create() {

	SLList * list = (SLList *) malloc(sizeof(SLList));
	list->head = NULL;

	return list;
 







}

// Insert an element in the linked list. If name already exists substitute value. 
// Otherwise insert entry. Return 0 if name is not there.
int sllist_insert(SLLIST *sllist,  char * name, char * value) {
    SLListEntry * e = sllist->head;
    int exitst = 0;
    while(e != NULL) {
    	if(!strcmp(e->name,name)){
    		exist = 1;
    		e->value = strdup(value);
    	}
    	e = e->next;
    }

    return exist;








}

// Remove entry in single linked list. 
int sllist_remove(SLLIST *sllist, char * name) {
    SLListEntry * e = sllist->head;
    if(e != NULL){
    	SLListEntry * p = e;
        e = p->next;
        if(!strcmp(p->name,name)){
            free(p);
            sllist->head = e;
            return 1;
        }
    }
    //int exitst = 0;
    while(e != NULL) {
    	if(!strcmp(e->name,name)){
    		//exist = 1;
            p->next = e->next;
            free(e);
            return 1;
    		//e->value = strdup(value);
    	}
    	p = e;
    	e = e->next;
    }

    return 0;






}

// Return last entry in pname, pvalue. Return 0 if list is empty or 1 otherwise.
int sllist_last(SLLIST *sllist, char ** pname, char **pvalue) {
    SLListEntry * e = sllist->head;
    if(e== NULL){
        return 0;
    }
    while(e!=NULL){
        if()
    }


}

// Print linked list in the format:
// 0: name=name0 value=value0
// 1: name=name1 value=cvalue1
...
void sllist_print(SLLIST sllist) {
  





}

// Reverse the list. Use the existing list and nodes. Do not allocate a new SLLIST nor use an array.
void sllist_reverse(SLLIST * sllist) {
   






}
