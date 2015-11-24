
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSTACK 50

int
main(int argc,  char **argv)
{
	char stack[MAXSTACK];
	char * input = argv;
	char temp;
	int i = 0;
	int c = 0;
	while(i < strlen(input)){
		temp = input[i];
		if(temp == '('||temp == '{'||temp == '['){
			stack[c] = temp;
			c ++;
		}
		else if(temp == ')'||temp == ']'||temp == '}'){
			if(c-1 > 0){
				if(temp == ')' && stack[c-1] != '('){
					printf("string is not balanced\n");
					return;
				}
				else{
					c--;
				}
				if(temp == ']' && stack[c-1] != '['){
					printf("string is not balanced\n");
					return;
				}
				else {
					c--;
				}
				if(temp == '}' && stack[c-1] != '{'){
					printf("string is not balanced\n");
					return;
				}
				else{
					c--;
				}
			}
			else{
				printf("string is not balanced\n");
			}
		}
		i++;
	}
	if(c == 0 && strlen(input) >1 ){
		printf("string is balanced\n");
	}
	else{
		printf("string is not balanced\n");
	}
	
}

