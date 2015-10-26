#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int need[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
const int maxn = 505;

int N, M;
ll dp[maxn][2][2][2];

ll dfs (int n, int p, int b, int c) {
	if (n < 0) return 0;

	ll& ret = dp[n][p][b][c];

	if (ret != -1) return ret;
	if (((n == need[1] && p) || (n == 0 && p == 0)) && b && c)
		return ret = 1;
	if (n == 0) return 0;
	ret = 0;

	if (b == 0 && c == 0) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				int x = (i + j + p) / 10, y = (i + j + p) % 10;
				ret += dfs(n-need[i]-need[j]-need[y], x, 0, 0);
				if (i)
					ret += dfs(n-need[i]-need[j]-need[y], x, 1, 0);
				if (j)
					ret += dfs(n-need[i]-need[j]-need[y], x, 0, 1);
				if (i&&j)
					ret += dfs(n-need[i]-need[j]-need[y], x, 1, 1);
				ret %= M;
			}
		}
	} else if (b == 0) {
		for (int i = 0; i < 10; i++) {
			int x = (i + p) / 10, y = (i + p) % 10;
			ret += dfs(n-need[i]-need[y], x, 0, 1);
			if (i)
				ret += dfs(n-need[i]-need[y], x, 1, 1);
			ret %= M;
		}
	} else if (c == 0) {
		for (int i = 0; i < 10; i++) {
			int x = (i + p) / 10, y = (i + p) % 10;
			ret += dfs(n-need[i]-need[y], x, 1, 0);
			if (i)
				ret += dfs(n-need[i]-need[y], x, 1, 1);
			ret %= M;
		}
	}
	return ret % M;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%d%d", &N, &M);
		memset(dp, -1, sizeof(dp));
		printf("Case #%d: %lld\n", kcas, dfs(N-3, 0, 0, 0));
	}
	return 0;
}
