
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>

#include "rpn.h"
#include "nextword.h"
#include "stack.h"

double rpn_eval(char * fileName, double x) {

  double a, b, c;
  FILE *fd;
  // Open file in fileName it.
   fd = fopen(fileName,"r");
    char * word;
	int jud = 0;
	//int lastVal = 0;
	//int lastTop = 0;
    while ((word = nextword(fd)) != NULL) {
    	//printf("%c\n",*word);
    	//printf("%d\n", (*word =='*'));
    	if(*word == '+'||(*word == '-' && word[1] == '\0') || *word == '*' || *word == '/' || !strcmp(word,"cos") || !strcmp(word,"sin") 
    		|| !strcmp(word,"exp") || !strcmp(word,"log") || !strcmp(word,"pow")){
					if(jud!=2) {jud = 1;}
    			    a = stack_pop();
    				if(stack_top()>0) { b = stack_pop(); 
					//printf("enter\n"); 
					} else { 
					//printf("false\n");
					jud = 2;
					}
    			if(*word == '+') {
    				stack_push(a+b);
    			} else if (*word == '-') {
    				stack_push(b - a);
    			} else if (*word == '*') {
					//printf("%f %f\n", a,b);
    				stack_push(a * b);
    			} else if (*word == '/') {
					//printf("%f %f\n", a,b);
    				stack_push(b / a);
    			} else if (!strcmp(word,"exp")) {
					jud = 1;
    				stack_push(b);
    				stack_push(exp(a));
    			} else if (!strcmp(word,"pow")) {
    				stack_push(pow(b,a));
    			} else if (!strcmp(word,"sin")) {
					jud = 1;
    				stack_push(b);
    				stack_push(sin(a));
    			} else if (!strcmp(word,"log")) {
					jud = 1;
    				stack_push(b);
    				stack_push(log(a));
    			} else if (!strcmp(word,"cos")) {
					jud = 1;
    				stack_push(b);
    				stack_push(cos(a));
    			}
				
//printf("%d\n",stack_top());
				//lastVal = stack_pop();
				//stack_push(lastVal);
				//lastTop = stack_top();
    	} else if(*word == 'x') {
    		stack_push(x);
    	} else {
    		stack_push(atof(word));
    	}
    }
    // Add your implementation here
    //
 
  // Check for errors
  //
  // Return result
  double result =  stack_pop();
  if(jud == 0) { printf("Elements remain in the stack\n"); exit(1);}
  if(jud == 2) { printf("Stack underflow\n"); exit(1);}
  return result;
}

