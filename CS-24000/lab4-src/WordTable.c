
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "WordTable.h"

// Initializes a word table
void wtable_init(WordTable * wtable)
{
	// Allocate and initialize space for the table
	wtable->nWords = 0;
	wtable->maxWords = 10;
	wtable->wordArray = (WordInfo *) malloc(wtable->maxWords * sizeof(WordInfo));
	for (int i = 0; i < wtable->maxWords; i++) {
		llist_init(&wtable->wordArray[i].positions);
	}
}

// Add word to the tableand position. Position is added to the corresponding linked list.
void wtable_add(WordTable * wtable, char * word, int position)
{
	// Find first word if it exists
	for (int i = 0; i < wtable->nWords; i++) {
		if ( strcmp(wtable->wordArray[i].word, word)== 0 ) {
			// Found word. Add position in the list of positions
			llist_insert_last(&wtable->wordArray[i].positions, position);
			return;
		}
	}

	// Word not found.

	// Make sure that the array has space.
	// Expand the wordArray here.
	if(wtable->nWords>=wtable->maxWords){
		wtable->maxWords += 1;
		wtable->wordArray = (WordInfo *) realloc(wtable->wordArray,wtable->maxWords * sizeof(WordInfo));
		for (int i = wtable->nWords; i < wtable->maxWords; i++) {
			llist_init(&wtable->wordArray[i].positions);
		}
	}

	// Add new word and position
	wtable->wordArray[wtable->nWords].word = strdup(word);
	llist_insert_last(&wtable->wordArray[wtable->nWords].positions, position);
	wtable->nWords++;
}

// Print contents of the table.
void wtable_print(WordTable * wtable, FILE * fd)
{
	fprintf(fd, "------- WORD TABLE -------\n");

	// Print words
	for (int i = 0; i < wtable->nWords; i++) {
		fprintf(fd, "%d: %s: ", i, wtable->wordArray[i].word);
		llist_print( &wtable->wordArray[i].positions);
	}
}

// Get positions where the word occurs
LinkedList * wtable_getPositions(WordTable * wtable, char * word)
{
	// Write your code here
		for (int i = 0; i < wtable->maxWords; i++) {
		//llist_init(&wtable->wordArray[i].positions);
		if(!strcmp(wtable->wordArray[i].word,word)){
			return (LinkedList *) &wtable->wordArray[i].positions;
		}
	}
	//LinkedList rVal = wtable
	return NULL;
}

//
// Separates the string into words
//

#define MAXWORD 200
char word[MAXWORD];
int wordLength;
int wordCount;
int charCount;
int wordPos;

// It returns the next word from stdin.
// If there are no more more words it returns NULL.
// A word is a sequence of alphabetical characters.
static char * nextword(FILE * fd) {
  	int c;
	char * nw = NULL;
	wordLength = 0;
	charCount = 0;
	if(fd == NULL) {
		return NULL;
	}
	while(((c=fgetc(fd))!=-1) && (( c == '\n'|| c=='\t' || c ==' ' || c == '\r') || (c < 'A'|| (c > 'Z' && c < 'a') || (c > 'z')))) {
		charCount++;
		//printf("%d\n", charCount);
	}
	
	
	while ((c!=-1)&&( c != '\n' && c!= ' ' && c!= '\r' && c!= '\t') && ((c >= 'a'&& c <= 'z') || (c >= 'A' && c <= 'Z')) ) { // While it is not EOF read char

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
}

// Conver string to lower case
void toLower(char *s) {
	int i;
	for(i = 0; i < strlen(s); i++) {
		if(s[i] >= 'A' && s[i] <= 'Z') {
			s[i] += 32;
		}
	}
	// Write your code here
}


// Read a file and obtain words and positions of the words and save them in table.
int wtable_createFromFile(WordTable * wtable, char * fileName, int verbose)
{
	// Write your code here
	//WordTable * wtable
	FILE * file = fopen(fileName,"r");
	wordPos = 0;
	wordCount = 0;
	char * wd = "";
	if(file == NULL){
		return 0;
	}
	while((wd = nextword(file)) != NULL) {
		//printf("%d\n", charCount);
		toLower(wd);
		wordPos += charCount;
		wtable_add(wtable,wd,wordPos);
		
		if(verbose == 1) {
			printf("%d: word=%s, pos=%d\n",wordCount, wd, wordPos);
			
		}
		wordPos += wordLength+1;
		//wordPos += (charCount + wordLength);
		wordCount ++;
	}
	return 0;
}

// Sort table in alphabetical order.
void wtable_sort(WordTable * wtable)
{
	//ListNode * p = list->head;
  //double find = *p;
	//ListNode * pend = NULL;
	//int c = n;
	WordInfo temp;
	int count = 0;
	int i;
	for(;count < wtable->nWords-1;count++){
	//printf("1\n");
	//pend = p->next;
	for(i=count+1; i < wtable->nWords;i++){
      if(strcmp(wtable->wordArray[count].word,wtable->wordArray[i].word) > 0) {
      	//printf("%s\n",wtable->wordArray[count].word);
		//printf("%s\n",wtable->wordArray[i].word);
        temp = wtable->wordArray[count];
        wtable->wordArray[count] = wtable->wordArray[i];
        wtable->wordArray[i] = temp;
      }
      //printf("%d",pend->value);
      //pend = pend->next;
    }
  }
	// Write your code here
}

// Print all segments of text in fileName that contain word.
// at most 200 character. Use fseek to position file pointer.
// Type "man fseek" for more info. 
int wtable_textSegments(WordTable * wtable, char * word, char * fileName)
{
	
	FILE * file = fopen(fileName,"r");
	if(file == NULL){
		return 0;
	}
	int i;
	int pp = 0;
	int * pos;
	char c;
	for (i = 0; i < wtable->nWords; i++) {
		if ( strcmp(wtable->wordArray[i].word, word)== 0 ) {
			// Found word. Add position in the list of positions
			//llist_insert_last(&wtable->wordArray[i].positions, position);
			//return;
			pp = i;
			break;
		}
	}
	
	printf("===== Segments for word \"%s\" in book \"%s\" =====\n",word,fileName);
	
	for(i=0;i<llist_number_elements(&wtable->wordArray[pp].positions);i++){
		llist_get_ith(&wtable->wordArray[i].positions,i,pos);
		printf("---------- pos=%d-----\n",pos);
		printf("......");
		file = fopen(fileName,"r");
		fseek(file,*pos,SEEK_SET);
		for(int k = 0; (k < 200 && ((c=fgetc(file))!=-1)); k++) {
			printf("%c",c);
		}
		printf("......\n");
	}
	
	// Write your code here
}

