#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;
const int maxn = 1e6;

int N, A[maxn + 5], P[maxn + 5], T[maxn + 5], fenw[maxn + 5];
ll dp[maxn + 5];

#define lowbit(x) ((x)&(-x))
void add (int x, int d) {
	while (x <= maxn) {
		fenw[x] += d;
		x += lowbit(x);
	}
}

int sum(int x) {
	int ret = 0;
	while (x) {
		ret += fenw[x];
		x -= lowbit(x);
	}
	return ret;
}

void init () {
	int x;
	memset(T, -1, sizeof(T));
	memset(fenw, 0, sizeof(fenw));

	for (int i = 1; i <= N; i++) {
		scanf("%d", &x);
		A[i] = x;

		if (T[x] == -1)
			P[i] = N;
		else
			P[i] = i - T[x];
		T[x] = i;
		add(P[i], 1);
	}
}

void solve() {
	memset(T, 0, sizeof(T));

	int c = 1;
	dp[1] = N;
	T[A[N]] = 1;

	for (int i = 2; i <= N; i++) {
		add(P[i-1], -1);
		int v = sum(maxn) - sum(i-1);
		dp[i] = dp[i-1] + v - c;
		if (T[A[N-i+1]] == 0) {
			T[A[N-i+1]] = 1;
			c++;
		}
	}
}

int main () {
	while (scanf("%d", &N) == 1 && N) {
		init();
		solve();
		int Q, x;
		scanf("%d", &Q);
		while (Q--) {
			scanf("%d", &x);
			printf("%I64d\n", dp[x]);
		}
	}
	return 0;
}
