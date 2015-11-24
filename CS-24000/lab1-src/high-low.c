#include <stdio.h>

int calc(int high, int low) {
  return (high+low)/2;
}
main(int argc, char **argv) {
  int high;
  int low;
  int avg;
  char c;
  char fi = 'y';
  printf("Welcome to the High Low game...\n");
  while(fi == 'y') {
    high = 100;
    low = 1;
    avg = 50;

    printf("Think of a number between 1 and 100 and press press <enter>");
    getchar();
    
    while (high>=low ) {
     printf("Is it higher than %d? (y/n)\n",avg);
     c = getchar();
     getchar();
     if( c == 'y' || c == 'Y') {
     	low = avg+1;
	avg = calc(high,low);
     } else if ( c == 'n' || c == 'N') {
     	high = avg-1;
	avg = calc(high,low);
	
     } else {
        printf("Type y or n\n");
}
  }
  printf("\n");
  printf(">>>>>> The number is %d\n",(high+1)); 
  printf("\n");
  printf("Do you want to continue playing (y/n)?");
  fi = getchar();
  getchar();
  //if(c == 'n' || c == 'N') {

  //  break;
  //  }
  } 
  printf("Thanks for playing!!!\n");
}
