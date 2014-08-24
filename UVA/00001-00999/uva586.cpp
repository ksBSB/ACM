#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 105;

int a[maxn];
char order[maxn];

void dfs (int n, int k) {
	int op = 0, x;

	while (scanf("%s", order) == 1 && strcmp(order, "END") ) {
		if (strcmp(order, "LOOP") == 0) {

			scanf("%s", order);
			if (strcmp(order, "n") == 0)
				dfs(n+1, k);
			else {
				sscanf(order, "%d", &x);
				dfs(n, k * x);
			}

		} else if (strcmp(order, "OP") == 0) {
			scanf("%d", &x);
			op += x;
		}
	}
	a[n] += op * k;
}

void put (int i, int flag) {
	if (a[i] == 0)
		return;

	if (flag)
		printf("+");

	if (a[i] > 1 && i)
		printf("%d*", a[i]);
	else if (i == 0)
		printf("%d", a[i]);

	if (i)
		printf("n");

	if (i > 1)
		printf("^%d", i);
}

int main () {
	int cas;
	scanf("%d", &cas);

	for (int kcas = 1; kcas <= cas; kcas++) {
		memset(a, 0, sizeof(a));

		scanf("%s", order);
		dfs(0, 1);

		int mv = 10;
		while (mv >= 0 && a[mv] == 0) mv--;

		printf("Program #%d\nRuntime = ", kcas);
		if (mv != -1) {
			put(mv, 0);
			for (int i = mv-1; i >= 0; i--)
				put(i, 1);
		} else
			printf("0");
		printf("\n\n");
	}
	return 0;
}
