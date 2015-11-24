
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSTACK 50
int isBalanced( char*str){
	char *stack = (char*) malloc(strlen(str)*sizeof(char));
	char *head = stack;
	char *p = str;

	while ( *p != '\0' ){
		if( *p=='(' || *p=='{' ){
			*stack=*p;
			stack++;
		} else if (*p==')'){
			if( *(stack-1)=='(' ){
				stack--;
			} else {
				return 0;
			}
		} else if (*p=='}'){
			if( *(stack-1)=='{' ){
				stack--;
			} else {
				return 0;
			}
		}
		p++;
	}
	if( stack==head && (strlen(str) %2 )== 0 ){
		return 1;
	} else {
		return 0;
	}
}

int
main(int argc,  char **argv)
{
	if( isBalanced(argv[1]) ){
		printf("string is balanced\n");
	} else {
		printf("string is not balanced\n");
	}
}


