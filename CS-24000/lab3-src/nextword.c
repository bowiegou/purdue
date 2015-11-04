
#include <stdio.h>
#include <stdlib.h>

//
// Separates the file into words
//

#define MAXWORD 200
char word[MAXWORD];
int wordLength;

// It returns the next word from fd.
// If there are no more more words it returns NULL. 
char * nextword(FILE * fd) {
  	int c;
	char * nw = NULL;
	wordLength = 0;
	
	if(fd == NULL) {
		return NULL;
	}
	while(((c=fgetc(fd))!=-1) && ( c == '\n'|| c=='\t' || c ==' ' || c == '\r') ){
	;
	}
	
	
	while ((c!=-1)&&( c != '\n' && c!= ' ' && c!= '\r' && c!= '\t')) { // While it is not EOF read char

		word[wordLength++] = c;
		
		nw = word;
		nw[wordLength] = '\0';// store character in word
		c = fgetc(fd);
		
		
		}
		if(wordLength == 0) {
		return NULL;
		} else 
		{
		return nw;
		}
		// if char is not in word return word so far.
		//
	// Return null if there are no more words
}

