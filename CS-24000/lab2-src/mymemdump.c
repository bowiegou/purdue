	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>

	void mymemdump(FILE * fd, char * p , int len) {
	 // Add your code here.
	 // You may see p as an array.
	 // p[0] will return the element 0 
	 // p[1] will return the element 1 and so on
	 
		 unsigned char sco[17];
		 unsigned long add = (unsigned long) p;
		 int a;
	 
		for (a = 0; a < len; a++) {
			
			if(a % 16 == 0) {
				if (a != 0) {
					fprintf (fd, "  %s\n", sco);
				}
								fprintf(fd, "0x%016lX:", (unsigned long) add);
				add += 0x10;
			}
			int c = p[a]&0xFF;
			

		 // Print first byte as hexadecimal
				fprintf(fd, " %02X", c);


		 // Print first byte as character
		 //fprintf(fd, "%c", (c>=32)?c:'.');
		 //fprintf(fd,"\n");
				if ((p[a] < 32) || (p[a] > 127))
					sco[a % 16] = '.';
				else
					sco[a % 16] = p[a];
				sco[(a % 16) + 1] = '\0';
		 
		}
		    while ((a % 16) != 0) {
		          fprintf (fd, "   ");
			            a++;
				        }
		fprintf (fd, "  %s\n", sco);
}
