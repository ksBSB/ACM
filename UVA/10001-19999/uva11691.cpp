#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = (1<<20)+5;
const int M = 30;
const int INF = 0x3f3f3f3f;

int n, c[M], dp[N][10];

void init () {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &c[i]);
	memset(dp, -1, sizeof(dp));
}

int dfs (int s, int k) {
	if (dp[s][k] != -1)
		return dp[s][k];

	if (s == ((1<<n)-1))
		return k;

	int& ans = dp[s][k];
	ans = INF;

	int v[10];
	memset(v, 0, sizeof(v));

	for (int i = 0; i < n; i++) {

		if (s&(1<<i))
			continue;

		if (v[c[i]])
			continue;
		v[c[i]] = 1;

		int tmp = dfs(s^(1<<i), max(0, c[i]-k-1)) + k + 1;
		ans = min(ans, tmp);
	}
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%d\n", dfs(0, 0));
	}
	return 0;
}
