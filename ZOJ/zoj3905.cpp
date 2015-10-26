#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 805;

struct State {
	int a, b;
	State (int a = 0, int b = 0): a(a), b(b) {}
	bool operator < (const State& u) const {
		if (b != u.b) return b > u.b;
		return a < u.a;
	}
}S[maxn];

int N, dp[maxn], tmp[maxn];

int solve () {
	memset(dp, 0, sizeof(dp));
	for (int i = 1; i <= N; i++) {
		memcpy(tmp, dp, sizeof(dp));
		for (int j = 1; j <= (i>>1); j++)
			dp[j] = max(dp[j], tmp[j-1] + S[i].a);
	}
	return dp[N>>1];
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &N);
		for (int i = 1; i <= N; i++)
			scanf("%d%d", &S[i].a, &S[i].b);
		sort(S + 1, S + N + 1);
		printf("%d\n", solve());
	}
	return 0;
}
