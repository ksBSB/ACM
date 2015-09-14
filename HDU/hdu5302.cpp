#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int N;

int jump(int p, int k) {
	if (p == N)
		return 2;
	p += k;
	if (p > N)
		return p - 1;
	return p;
}

void solve (int n, int a1, int a2, int k) {
	int p = 1;
	for (int i = 0; i <= a2; i++) {
		int t = jump(p, k + 1);
		printf("%d %d %d\n", p, t, k);
		p = t;
	}
	p = jump(p, k + 1);
	for (int i = 1; i < a1; i++) {
		int t = jump(p, k + 1);
		printf("%d %d %d\n", p, t, k);
		p = jump(t, k + 1);
	}
}

int main () {
	int cas, w0, w1, w2, b0, b1, b2;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d%d%d%d%d", &w0, &w1, &w2, &b0, &b1, &b2);
		N = w0 + w1 + w2;

		if ((w1&1) || (b1&1)) {
			printf("-1\n");
			continue;
		}

		printf("%d\n", w1 / 2 + b1 / 2 + w2 + b2);
		solve(N, w1 / 2, w2, 0);
		solve(N, b1 / 2, b2, 1);
	}
	return 0;
}
