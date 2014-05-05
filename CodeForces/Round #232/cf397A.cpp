#include <stdio.h>
#include <string.h>

const int N = 105;

int n, v[N], L, R;

int main () {
	memset(v, 0, sizeof(v));
	scanf("%d%d%d", &n, &L, &R);	

	int x, y;
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &x, &y);
		for (int j = x + 1; j <= y; j++) v[j] = 1;
	}

	int ans = 0;
	for (int i = L + 1; i <= R; i++) if (!v[i])
		ans++;
	printf("%d\n", ans);
	return 0;
}
