#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1005;

struct State {
	int a, b, t;
	State(int a = 0, int b = 0, int t = 0):a(a), b(b), t(t) {}
	bool operator < (const State& u) const {
		return u.b * t < b * u.t;
	}
}G[maxn];

int N, T, dp[3 * maxn];

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d", &N, &T);
		memset(dp, 0, sizeof(dp));
		int a, b, t;
		for (int i = 0; i < N; i++) {
			scanf("%d%d%d", &a, &b, &t);
			G[i] = State(a, b, t);
		}
		sort(G, G + N);

		for (int i = 0; i < N; i++) {
			a = G[i].a, b = G[i].b, t = G[i].t;
			for (int j = T; j >= t; j--)
				dp[j] = max(dp[j], dp[j-t] + a - b * j);
		}
		int ans = 0;
		for (int i = 0; i <= T; i++) ans = max(ans, dp[i]);
		printf("%d\n", ans);
	}
	return 0;
}
