#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "bits.h"
// It prints the bits in bitmap as 0s and 1s.
void printBits(unsigned int bitmap)
{
	int i;
	unsigned long result=0x80000000;
	for(i=0;i<32;++i)
    { 
      if( (result&bitmap) != 0){printf("1",result,bitmap, i);}
      else{printf("0",result,bitmap, i);}
      result=result>>1;
	  
    }
	printf("\n");
	printf("10987654321098765432109876543210\n");
	//printf("%d\n"
	// Add your code here
}


// Sets the ith bit in *bitmap with the value in bitValue (0 or 1)
void setBitAt( unsigned int *bitmap, int i, int bitValue ) {
	unsigned int bitmask=(1<<i);
	if(bitValue){
		*bitmap=((*bitmap)|bitmask);
	}else{
		*bitmap=((*bitmap)&(~bitmask));
	}
}

// It returns the bit value (0 or 1) at bit i
int getBitAt( unsigned int bitmap, unsigned int i) {
	unsigned int bitmask=(1<<i);
	return (bitmask&bitmap)?1:0;
}

// It returns the number of bits with a value "bitValue".
// if bitValue is 0, it returns the number of 0s. If bitValue is 1, it returns the number of 1s.
int countBits( unsigned int bitmap, unsigned int bitValue) {
	unsigned int bitmask;
	int count0,count1,i;
	for(i=0,count1=0,count0=0;(i<32)&&(bitmask=(1<<i));i++)
		(bitmap&bitmask)?count1++:count0++;
	return (bitValue)?count1:count0;

}

// It returns the number of largest consecutive 1s in "bitmap".
// Set "*position" to the beginning bit index of the sequence.
int maxContinuousOnes(unsigned int bitmap, int * position) {
	int arr[40][2],i,j,in,count,max;
	unsigned int bitmask=1;
	for(i=0,j=0,in=0,count=0,max=0;(i<32)&&(bitmask=(1<<i));i++){
	  if(bitmask&bitmap){
			count++;
	  }else{
		  if(count>0){
		    arr[j][0]=count;
		    arr[j++][1]=i-count;
		  }
		  count=0;
		}	
	}
	for(i=0;i<j;i++)
		if(arr[i][0]>arr[max][0])
			max=i;
	*position=arr[max][1];
	return arr[max][0];
}


