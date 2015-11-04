
// Data structs for a list of ints

struct ListNodeLink {
	char * value;
	struct ListNodeLink * next;
};

typedef struct ListNodeLink ListNodeLink;

struct LinkedList {
	ListNodeLink * head;
};

typedef struct LinkedList LinkedList;

void llist_init(LinkedList * list);
void llist_print(LinkedList * list);
void llist_add(LinkedList * list, char * value);
int llist_exists(LinkedList * list, char * value);
int llist_remove(LinkedList * list, char * value);
int llist_get_ith(LinkedList * list, int ith, char ** value);
int llist_remove_ith(LinkedList * list, int ith);
int llist_number_elements(LinkedList * list);
int llist_save(LinkedList * list, char * file_name);
int llist_read(LinkedList * list, char * file_name);
void llist_sort(LinkedList * list, int ascending);
void llist_clear(LinkedList *list);

int llist_remove_first(LinkedList * list, char * value);
int llist_remove_last(LinkedList * list, char * value);
void llist_insert_first(LinkedList * list, char * value);
void llist_insert_last(LinkedList * list, char * value);
