/*******************
 * 取到最后一个石子的输
 * ****************/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 30;
const int maxs = 1<<14;

int N, S, m[maxn];
int dp[maxn][maxs];

void init () {
	memset(dp, -1, sizeof(dp));

	scanf("%d", &S);
	for (int i = 0; i < 2 * N; i++)
		scanf("%d", &m[i]);
}

bool dfs (int d, int s) {

	if (s <= 0)
		return 1;

	if (d >= 2 * N)
		d -= 2 * N;

	if (dp[d][s] != -1)
		return dp[d][s];

	dp[d][s] = 0;

	for (int i = 1; i <= m[d]; i++) {
		if (dfs(d + 1, s - i))
			continue;

		dp[d][s] = 1;
	}
	return dp[d][s];
}

int main () {
	while (scanf("%d", &N) == 1 && N) {
		init();
		printf("%d\n", dfs(0, S) ? 1 : 0);
	}
	return 0;
}
