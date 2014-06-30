#include<stdio.h>
#include<string.h>
#define N 10005
int main(){
	int k, n, p[N], q[N];
	while (scanf("%d", &k) != EOF){
		// Init.
		memset(p, 0, sizeof(p));
		memset(q, 0, sizeof(q));
		char c = '\0';
		n = 0;

		while (1){
			scanf("%d%c", &p[n++], &c);
			if (c == '\n')
				break;
		}

		q[0] = p[0];
		for (int i = 1; i < n; i++)
			q[i] = p[i] + k * q[i - 1];
		
		// Printf.
		printf("q(x):");
		for (int i = 0; i < n - 1; i++)
			printf(" %d", q[i]);
		printf("\nr = %d\n", q[n - 1]);
		printf("\n");
	}
	return 0;}
