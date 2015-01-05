#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 4000005;
const int maxm = 80005;

#define lowbit(x) ((x)&(-x))
int N, M, W, E, H[maxn+5], fenw[maxn + 5];
int O[maxm], X[maxm], Y[maxm], Z[maxm];

inline int find (int x) {
	return lower_bound(H + 1, H + E, x) - H;
}

void hashPoint (int x, int y) {
	for (int i = x; i <= W; i += lowbit(i)) {
		for (int j = y; j <= W; j += lowbit(j))
			H[E++] = i * W + j;
	}
}

void add(int x, int y, int d) {
	for (int i = x; i <= W; i += lowbit(i)) {
		for (int j = y; j <= W; j += lowbit(j)) {
			int pos = find(i * W + j);
			fenw[pos] += d;
		}
	}
}

int sum (int x, int y) {
	int ret = 0;
	for (int i = x; i; i -= lowbit(i)) {
		for (int j = y; j; j -= lowbit(j)) {
			int pos = find(i * W + j);
			if (H[pos] == i * W + j)
				ret += fenw[pos];
		}
	}
	return ret;
}

void init () {
	E = 1;
	W = 2 * N;
	scanf("%d", &M);
	memset(fenw, 0, sizeof(fenw));

	for (int i = 1; i <= M; i++) {
		scanf("%d%d%d%d", &O[i], &X[i], &Y[i], &Z[i]);
		int x = X[i] - Y[i] + N;
		int y = X[i] + Y[i];
		if (O[i] == 1)
			hashPoint(x, y);
	}
	sort(H + 1, H + E);
	E = unique(H + 1, H + E) - H;
}

void solve() {
	for (int i = 1; i <= M; i++) {
		int x = X[i] - Y[i] + N;
		int y = X[i] + Y[i];

		if (O[i] == 1)
			add(x, y, Z[i]);
		else {
			int a = max(1, x - Z[i]);
			int b = max(1, y - Z[i]);
			int c = min(W, x + Z[i]);
			int d = min(W, y + Z[i]);
			printf("%d\n", sum(c, d) - sum(c, b-1) - sum(a-1, d) + sum(a-1, b-1));
		}
	}
}

int main () {
	while (scanf("%d", &N) == 1 && N) {
		init();
		solve();
	}
	return 0;
}
