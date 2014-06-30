#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 150;
const int M = 12;
const int INF = 0x3f3f3f3f;

int n, m, dp[1<<M][1<<M], s[N];

void init () {
	memset(dp, -1, sizeof(dp));

	char str[M];
	for (int i = 0; i < n; i++) {
		scanf("%s", str);
		int state = 0;
		for (int j = 0; j < m; j++) if (str[j] == '1')
			state = state | (1<<j);
		s[i] = state;
	}
}

int solve (int x, int y) {
	if (dp[x][y] != -1) return dp[x][y];
	dp[x][y] = INF;

	int c = 0;
	for (int i = 0; i < n; i++) {
		if ( (x&s[i]) == y) c++;
	}
	
	if (c <= 1) return dp[x][y] = 0;

	for (int i = 0; i < m; i++) {
		if (x&(1<<i)) continue;
		dp[x][y] = min(dp[x][y], max(solve(x|(1<<i), y), solve(x|(1<<i), y|(1<<i))) + 1);
	}
	return dp[x][y];
}

int main () {
	while (scanf("%d%d", &m, &n) == 2 && n + m) {
		init();
		printf("%d\n", solve(0, 0));
	}
	return 0;
}
