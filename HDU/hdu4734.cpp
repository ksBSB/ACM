#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 10000;

int n, bit[15];
int dp[15][maxn];

int init () {
	int s = n = 0, a, b;
	scanf("%d%d", &a, &b);

	for (int i = 0; a; i++) {
		s += (a % 10) * (1<<i);
		a /= 10;
	}

	while (b) {
		bit[n++] = b % 10;
		b /= 10;
	}
	return s;
}

int dfs (int d, int s, int flag) {
	
	if (d == -1)
		return (s >= 0);

	if (flag == 0 && dp[d][s] != -1)
		return dp[d][s];

	int ret = 0, end = (flag ? bit[d] : 9);
	for (int i = 0; i <= end; i++) {
		if (s < i * (1<<d))
			continue;
		ret += dfs(d - 1, s - i * (1<<d), flag && i == end);
	}

	if (flag == 0)
		dp[d][s] = ret;
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	memset(dp, -1, sizeof(dp));
	for (int kcas = 1; kcas <= cas; kcas++) {
		int f = init();
		printf("Case #%d: %d\n", kcas, dfs(n - 1, f, 1));
	}
	return 0;
}
