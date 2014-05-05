#include <stdio.h>
#include <string.h>

const int N = 50005;
const int M = 105;

int n, v[N];

void add(int x, int val) {
	while (x <= n) {
		v[x] += val;
		x += (x & (-x));
	}
}

void init() {
	memset(v, 0, sizeof(v));
	int a;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a);
		add(i, a);
	}
}

int sum(int x) {
	int ans = 0;
	while (x > 0) {
		ans += v[x];
		x -= (x & (-x));
	}
	return ans;
}

void solve() {
	int x, y;
	char order[M];

	while (scanf("%s", order) == 1 && strcmp(order, "End") ) {
		scanf("%d%d", &x, &y);
		if (order[0] == 'A') add(x, y);
		else if (order[0] == 'S') add(x, -y);
		else printf("%d\n", sum(y) - sum(x-1));
	}
}

int main() {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		printf("Case %d:\n", i);
		init();
		solve();
	}
	return 0;
}
