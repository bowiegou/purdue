
#include <stdio.h>

#include "array.h"

// Return sum of the array
double sumArray(int n, double * array) {
  double sum = 0;
  
  double * p = array;
  double * pend = p+n;

  while (p < pend) {
    sum += *p;
    p++;
  }

  return sum;
}

// Return maximum element of array
double maxArray(int n, double * array) {
  double * p = array;
  double max = *p;
  double * pend = p+n;

  while (p < pend) {
    if(*p > max){
      max = *p;
    }
    p++;
  }

  return max;
}

// Return minimum element of array
double minArray(int n, double * array) {
  double * p = array;
  double min = *p;
  double * pend = p+n;

  while (p < pend) {
    if(*p < min){
      min = *p;
    }
    p++;
  }

  return min;
}

// Find the position int he array of the first element x 
// such that min<=x<=max or -1 if no element was found
int findArray(int n, double * array, double min, double max) {
  double * p = array;
  //double find = *p;
  double * pend = p+n;
  int count = 0;

  while (p < pend) {
    if(*p>=min && *p <= max){
      return count;
    }
    count++;
    p++;
  }

  return -1;
}

// Sort array without using [] operator. Use pointers 
// Hint: Use a pointer to the current and another to the next element
int sortArray(int n, double * array) {
  double * p = array;
  //double find = *p;
  double * pend = p+n-1;
  //int c = n;
  double temp;
  for(;p < pend;p++){
    double * next = p+1;
    for(;next < pend+1;next++){
      if(*next < *p){
        temp = *p;
        *p = *next;
        *next = temp;
      }
    }
  }
}

// Print array
void printArray(int n, double * array) {
  double * p = array;
  double * pend = p+n;
  int count = 0;
  while (p < pend) {
    printf("%d:%.6f\n",count,*p);
    count++;
    p++;
  }

  //return sum;

}

