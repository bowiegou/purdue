
#include <stdlib.h>
#include "mystring.h"

// Type "man string" to see what every function expects.

int mystrlen(char * s) {
	int i = 0;
	while(*(s+i) != '\0'){
		i++;
	}
	return i;
}

char * mystrcpy(char * dest, char * src) {
	int i = mystrlen(src);
	int c;
	for(c=0;c<mystrlen(dest);c++) {
		*(dest+c) = '\0';
	}
	for(c = 0; c<i; c++) {
		*(dest+c) = *(src+c);
	}
	return dest;
}

char * mystrcat(char * dest, char * src) {
	char * rVal = dest;
	while(*dest != '\0') 
	             dest++;
	while((*dest++ = *src++) != '\0') 
		          ;
	return rVal;
}

int mystrcmp(char * s1, char * s2) {
	if(mystrlen(s1) > mystrlen(s2)) {
		return 1;
	}else if(mystrlen(s1) < mystrlen(s2)) {
		return -1;
	}else {
		int i;
		int len = mystrlen(s1);
		int rVal = 0;
		for(i = 0; i< len; i++) {
			if(*(s1+i) < *(s2+i)) {
				rVal --;
			}
			else if (*(s1+i) > *(s2+i)) {
				rVal ++;
				}

		}
		return rVal;
	}

	return 0;
}

char * mystrstr(char * hay, char * needle) {
	int nlen = mystrlen(needle);
	int haylen = mystrlen(hay);
	if (haylen < nlen) {
		return NULL;
	} else {
		int i;
		int inner;
		char * rVal = NULL;
		int innerj = 1;
		for(i=0;i<haylen-nlen+1; i++) {
			if(*(hay+i) == *needle) {
				innerj = 1;
				for(inner = 0; inner < nlen; inner ++) {
					if(*(hay+i+inner) != *(needle+inner)) {
						innerj = 0;;
					}
				}
				if(innerj == 1) {
					rVal = hay+i;
				}
			}
		}
	return rVal;
	}

}

char * mystrdup(char * s) {
	    char *d = malloc (mystrlen (s) + 1);   // Allocate memory
	    if (d != NULL) mystrcpy (d,s);         // Copy string if okay
	    return d;                            // Return new memory
}

char * mymemcpy(char * dest, char * src, int n){
	        //int i = mystrlen(src);
		int c;
	 	for(c = 0; c<n; c++) {
			 *(dest+c) = *(src+c);
		 }
	 return dest;

}

