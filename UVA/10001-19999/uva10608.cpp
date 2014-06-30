#include <stdio.h>
#include <string.h>
const int N = 30005;
int n, m, f[N], cnt[N];

int getfather(int x) {
	return x == f[x] ? x : f[x] = getfather(f[x]);
}

void init() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		f[i] = i;
		cnt[i] = 1;
	}
}

int solve() {
	int x, y, a, b, ans = 0;
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &a, &b);
		x = getfather(a), y = getfather(b);
		if (x == y) continue;
		f[y] = x;
		cnt[x] += cnt[y];
		if (cnt[x] > ans) ans = cnt[x];
	}
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}
