#include<stdio.h>
#include<string.h>
#define N 205
char tem[N][N];
int n;

void build(int k, int a, int b){
	for (int i = a; i < b; i++){
		if (tem[k][i] != '\0' && tem[k][i] != ' '){
			putchar(tem[k][i]);
			putchar('(');
			if (k + 1 < n && tem[k + 1][i] == '|'){
				int p, q;
				for (p = i; p >= 0 && tem[k + 2][p] == '-'; p--);
				for (q = i; q < strlen(tem[k + 2]) && tem[k + 2][q] == '-'; q++);
				build(k + 3, p, q);
			}
			putchar(')');
		}
	}
}

int main(){
	int t;
	scanf("%d%*c", &t);
	while (t--){
		// Init.
		memset(tem, 0, sizeof(tem));
		n = 0;

		// Read.
		while (gets(tem[n]) != NULL){
			if (strcmp(tem[n], "#") == 0)
				break;
			n++;
		}

		// Handle.
		putchar('(');
		if (n != 0)
			build(0, 0, strlen(tem[0]));
		putchar (')');
		printf("\n");
	}
	return 0;}
