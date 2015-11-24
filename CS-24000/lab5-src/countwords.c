
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct WordInfo {
	char * word;
	int count;
};

typedef struct WordInfo WordInfo;

int maxWords;
int nWords;
WordInfo*  wordArray;

#define MAXWORD 100
int wordLength;
char word[MAXWORD];
FILE * fd;
int charCount;
int wordPos;
char t[100];

void toLower(char *s) {
	int i;
	for(i = 0; i < strlen(s); i++) {
		if(s[i] >= 'A' && s[i] <= 'Z') {
			s[i] += 32;
		}
	}
}

// It returns the next word from stdin.
// If there are no more more words it returns NULL. 
static char * nextword() {
	char * w; char * tw = t;
	while((*w=fgetc(fd))!=-1 && (*w == ' ' || *w == '.'||*w == '\t'|| *w == '\n'))
		;
	t[0] = *w;
	while((*w=fgetc(fd))!=-1 && (*w != ' ' || *w != '.'||*w != '\t'|| *w != '\n')) {
		tw ++;
		toLower(w);
		*tw = w;
	}
	tw++;
	*tw = '\0';
	return &t[0];

    
}

int
main(int argc, char **argv)
{
	if (argc < 2) {
		printf("Usage: countwords filename\n");
		exit(1);
	}

	char * filename = argv[1];

	fd = fopen(filename, "r");
	fgets(word,1000,stdin);
	int count = 0;
	char kkk[100];
	char * w = kkk;
	nWords = 0;
	maxWords = 100;
	wordArray = (WordInfo*) malloc(sizeof(WordInfo) * maxWords);
	while((w=nextword())!=NULL) {
		int jud = -1;
		int i;
		for(i =0; i < nWords; i++) {
			if(strcmp(wordArray[i].word,w) == 0)
				jud = i;
		}
		if(jud != -1)
			wordArray[i].count ++;
		else if(nWords < maxWords) {
			wordArray[nWords].word = w;
			wordArray[nWords++].count = 1;
		}
		else{
			wordArray = (WordInfo*) realloc(wordArray,sizeof(WordInfo)*(++maxWords));
			wordArray[nWords].word = w;
			wordArray[nWords++].count = 1;
		}
		WordInfo temp;
		
		int j;
		for(i = 0; i < nWords-1; i++) {
			for(j = i; j < nWords; j++) {
				if(strcmp(wordArray[i].word, wordArray[j].word) > 0){
					temp = wordArray[i];
					wordArray[j] = wordArray[i];
					wordArray[j] = temp;
			}
		}
		}
		for( i = 0; i < nWords; i++) {
			printf("%s %d\n",wordArray[i].word,wordArray[i].count);
		}
	}
		
	

}

