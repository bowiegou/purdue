#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	printf("Input Matrix:\n");
	int m,n,i,j;
	scanf("%d%d",&m,&n);
	float mat[m][n+1];
	for(i = 0; i < m; i++) {
		for(j = 0; j < n; j++) {
			scanf("%f",&mat[i][j]);
		}
	}
	for(i = 0; i < m; i++) {
		for(j = 0; j < n; j++) {
			printf("%f ",mat[i][j]);
		}
		printf("\n");
	}
	
}