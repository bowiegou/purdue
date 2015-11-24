
#include <stdlib.h>


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

char * mystrncpy( char *dst, const char *src, int num )  
{  
    char  * adress = dst;  
  
    while ( num-- != 0 )  
    {  
        while ( ( *dst++ = *src++ ) != '\0' )  
            ;  
    }  
  
    return  adress;  
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

char * mystrtrim(char * s) {
	char * t = s;
	//int c = 0;
	while(*t == ' ' || *t == '\t'){
		t++;
	}
	char * end = t;
	while(*end != ' ') {
		end ++;
	}
	*end = '\0';
	memmove(s,t,mystrlen(t)+1);
	return s;
}

char * mystrreplace(char *str, char *str1, char *str2) {

        char *s;
        unsigned long int len;
        register unsigned long int i=0;
        char *temp;
        temp=str;
        while (mystrstr(temp,str1)!=NULL){
            temp=mystrstr(temp,str1)+mystrlen(str1);
                i++;}
        len=(mystrlen(temp)-mystrlen(str1)*i+mystrlen(str2)*i)*sizeof(char);
        s=(char *)malloc(len);
        if (s!=NULL){
        s="s";
        while (mystrstr(str,str1)!=NULL)
                {
                s=strncat(s,str,(mystrstr(str,str1)-str));
                s=mystrcat(s,str2);
                str=mystrstr(str,str1)+mystrlen(str1);}
    s=mystrcat(s,str);
    s=s+1;
    return(s);}
        else{
                return NULL;
				}
}

