
#include <stdio.h>
#include "stack.h"
#include <stdlib.h>

int top=0;
double stack[MAXSTACK];

void stack_clear() 
{
  top = 0;
}

double stack_pop()
{
	// Add implementation here`

	double rVal;
	if (top != 0) {

		return stack[top--];

	}
	else{
	
	return 0;
	}
}

void stack_push(double val)
{
	// Add implementation here
	top++;
	stack[top] = val;
	//printf("%d",top);
}

void stack_print()
{
	if(top != 0){
		printf("Stack:\n");
	
		int count = 0;
		for(int i = 1;i <= top; i++){
		printf("%d: %lf\n",count++,stack[i]);
		}
	}
	else {
		printf("Stack:\n");
		printf("Stack is empty");
	}
}

int stack_top()
{
  return top;
}

int stack_max()
{
  return MAXSTACK;
}

int stack_is_empty()
{
  return top == 0;
}


