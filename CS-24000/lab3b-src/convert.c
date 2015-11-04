#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//#include <math.h>
int main(int argc, char ** argv){
	if(argc != 4) {
		printf("Usage:  convert <basefrom> <baseto> <number>\n");
		exit(1);
	}
	 char numbase[25] =
	 {'0', '1', '2', '3', '4', '5', '6', '7',
	  '8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
	  'G','H','I','J','K','L','M','N','O'};

   int converted_number[32];
   int index;
   char * num =  argv[3];
   int number = 0;
   int numlen = strlen(argv[3]);
   //printf("%d", numlen);
   int numberoriginal ;
   int basefrom = atoi(argv[1]);
   int baseto = atoi(argv[2]);
   int i=0;

   /* get the number and base */
   //scanf("%ld %i", &number_to_convert, &base);

   //printf("%d %d %d", (power(15,0)),(power(16,1)),(power(16,2)));
   for(i = 1;i < numlen+1; i++) {
	   index = strchr(numbase,num[i-1]) - numbase ;
	   if(index  >= basefrom) {
		   printf("Number read in base %d: %s\n", basefrom,num);
		   printf("Wrong digit in number.\n");
		   exit(1);
	   }
	   //printf("%d ",index);
	   number +=  index*power(basefrom,(numlen-i));
	   //printf("%d ", number);
   }
   numberoriginal = number;
   i = 0;
   while (number != 0)
   {
	 converted_number[i] = number % baseto;
	 number = number / baseto;
	 i++;
   }

   i --;
   
   printf("Number read in base %d: %s\n", basefrom,num);
   printf("Converted to base 10: %d\n", numberoriginal);
   printf("Converted to base %d: ",baseto);
   for(  ; i>=0; i--) /* go backward through array */
   {
	 printf("%c", numbase[converted_number[i]]);
   }
   printf("\n");
}

 int power(int base, int exp)
{
    int result = 1;
    while(exp) { result *= base; exp--; }
    return result;
} 

/* int pow(int a, int p) {
	if(p == 0) {
		return 1;
	}
	int o = 1;
	int rVal = a;
	for(; o < p; o++) {
		rVal =  rVal* rVal;
	}
	return rVal;
} */
