#include "mysort.h"
#include <alloca.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//
// Sort an array of element of any type
// it uses "compFunc" to sort the elements.
// The elements are sorted such as:
//
// if ascending != 0
//   compFunc( array[ i ], array[ i+1 ] ) <= 0
// else
//   compFunc( array[ i ], array[ i+1 ] ) >= 0
//
// See test_sort to see how to use mysort.
//
void mysort( int n,                      // Number of elements
	     int elementSize,            // Size of each element
	     void * array,               // Pointer to an array
	     int ascending,              // 0 -> descending; 1 -> ascending
	     CompareFunction compFunc )  // Comparison function.
{
  int i,j,maxIndex,minIndex;
  void *current, *max, *min, *temp;
  if(ascending){
		for(i=0;i<n;i++){ 
			minIndex=i;
			for(j=i;j<n;j++){
				current=(void *)((char *)array+j*elementSize);
				min=(void *)((char *)array+minIndex*elementSize);
				if(compFunc(current,min)<0){
					minIndex=j;
				}
			}
			temp=malloc(elementSize);
			current=(void *)((char *)array+i*elementSize);
			min=(void *)((char *)array+minIndex*elementSize);
			memcpy(temp,min,elementSize);
			memcpy(min,current,elementSize);
			memcpy(current,temp,elementSize);
		}
  }else{
		for(i=0;i<n;i++){ 
			maxIndex=i;
			for(j=i;j<n;j++){
				current=(void *)((char *)array+j*elementSize);
				max=(void *)((char *)array+maxIndex*elementSize);
				if(compFunc(current,max)>0){
					maxIndex=j;
				}
			}
			temp=malloc(elementSize);
			current=(void *)((char *)array+i*elementSize);
			max=(void *)((char *)array+maxIndex*elementSize);
			memcpy(temp,max,elementSize);
			memcpy(max,current,elementSize);
			memcpy(current,temp,elementSize);
		}
  }
  free(temp);

}

