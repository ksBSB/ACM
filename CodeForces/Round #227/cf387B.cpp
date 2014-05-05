#include <stdio.h>
#include <string.h>

const int N = 1000005;
const int INF = 0x3f3f3f3f;

int n, m, a[N];

void init() {
	int k;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
}

int solve() {
	int ans = 0, p = 0, k;
	for (int i = 0; i < m; i++) {
		scanf("%d", &k);
		if (k >= a[p] && p < n) {
			p++; ans++;
		}
	}
	return ans;
}

int main () {
	init();
	printf("%d\n", n - solve());
	return 0;
}
