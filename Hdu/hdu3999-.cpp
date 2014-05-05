#include <stdio.h>
#include <string.h>

const int N = 1e6+5;

int n, c, node[N], ans[N];

void Insert (int u, int v) {
	if (node[u] == -1) {
		node[u] = v;
	} else if (node[u] > v) {
		Insert (u*2+1, v);
	} else {
		Insert (u*2+2, v);
	}
}

void preOrder (int u) {
	ans[c++] = node[u];

	if (node[u*2+1] != -1)
		preOrder (u*2+1);
	
	if (node[u*2+2] != -1)
		preOrder (u*2+2);
}

int main () {
	int a;
	while (scanf("%d", &n) == 1) {
		c = 0;
		memset(node, -1, sizeof(node));
		for (int i = 0; i < n; i++) {
			scanf("%d", &a);
			Insert(0, a);
		}
		preOrder (0);

		printf("%d", ans[0]);
		for (int i = 1; i < c; i++) 
			printf(" %d", ans[i]);
		printf("\n");
	}
	return 0;
}
