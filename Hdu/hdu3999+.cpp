#include <stdio.h>
#include <string.h>

const int N = 1e5+5;

int n, k, c, left[N], right[N], val[N], ans[N];

void insert (int u, int v) {
	if (val[u] == -1)
		val[u] = v;
	else if (val[u] > v) {

		if (left[u] == -1)
			left[u] = k;

		insert (left[u], v);
	} else {
		
		if (right[u] == -1)
			right[u] = k;
		insert (right[u], v);
	}
}

void preOrder (int u) {
	ans[c++] = val[u];
	if (left[u] != -1)
		preOrder (left[u]);
	if (right[u] != -1)
		preOrder (right[u]);
}

int main () {
	int a;
	while (scanf("%d", &n) == 1) {
		memset(left, -1, sizeof(left));
		memset(right, -1, sizeof(right));
		memset(val, -1, sizeof(val));

		for (k = 0; k < n; k++) {
			scanf("%d", &a);
			insert(0, a);
		}
		preOrder (0);

		printf("%d", ans[0]);
		for (int i = 1; i < n; i++)
			printf(" %d", ans[i]);
		printf("\n");
	}
	return 0;
}
