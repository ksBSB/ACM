#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 105;

struct Bign {
	int n, s[maxn<<1];

	Bign (int t = 0) { init(); s[0] = t; }

	void init () { n = 1; memset(s, 0, sizeof(s)); }
	void add(const Bign& a) {
		int res = 0;
		for (int i = 0; i < a.n || i < n; i++) {
			if (i < a.n) res += a.s[i];
			if (i < n) res += s[i];
			s[i] = res % 10;
			res /= 10;
		}

		n = max(a.n, n);
		while (res) {
			s[n++] = res % 10;
			res /= 10;
		}
	}
}dp[maxn][maxn], ONE(1);

int N, K, A[maxn];

void solve () {
	Bign ans(0);

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= K; j++)
			dp[i][j].init();
	}
	for (int i = 1; i <= N; i++) {
		dp[i][1].add(ONE);
		ans.add(dp[i][K]);
		for (int j = i + 1; j <= N; j++) if (A[i] < A[j]) {
			for (int k = 2; k <= K; k++) dp[j][k].add(dp[i][k-1]);
		}
	}

	for (int i = ans.n-1; i >= 0; i--) printf("%d", ans.s[i]);
	printf("\n");
}

int main () {
	while (scanf("%d%d", &N, &K) == 2) {
		for (int i = 1; i <= N; i++) scanf("%d", &A[i]);
		solve();
	}
	return 0;
}
