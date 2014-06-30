#include <stdio.h>
#include <string.h>

const int N = 30;
int n, vis[N];

void insert(int cur, int m) {
    for (int i = m; i > cur; i--)
	vis[i] = vis[i - 1];
    vis[cur] = m;
}

void handle(int deep) {
    for (int i = 0; i <= deep; i++)
	printf("  ");
    if (deep == n - 1) {
	printf("writeln(%c", vis[0] + 'a');
	for (int i = 1; i < n; i++)
	    printf(",%c", vis[i] + 'a');
	printf(")\n");
	return ;
    }

    int rec[N];
    for (int i = 0; i <= deep; i++)
	rec[i] = vis[i];

    for (int i = deep + 1; i >= 0; i--) {
	if (i)	{
	    printf("if %c < %c then\n", vis[i - 1] + 'a', deep + 1 + 'a');
	}
	insert(i, deep + 1);
	handle(deep + 1);
	memcpy(vis, rec, sizeof(rec));
	if(i) {
	    for (int i = 0; i <= deep; i++)
		printf("  ");
	    printf("else ");
	}
	if(i == 1)	printf("\n");
    }
}

int main() {
    int nCas;
    scanf("%d", &nCas);
    while (nCas--) {
	memset(vis, 0, sizeof(vis));
	scanf("%d", &n);

	printf("program sort(input,output);\nvar\na");
	for (int i = 1; i < n; i++)
	    printf(",%c", 'a' + i);
	printf(" : integer;\nbegin\n  readln(a");
	for (int i = 1; i < n; i++) 
	    printf(",%c", 'a' + i); 
	printf(");\n");

	handle(0);

	printf("end.\n");

	if (nCas)
	    printf("\n");
    }
    return 0;}
