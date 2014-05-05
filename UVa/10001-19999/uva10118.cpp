#include <stdio.h>
#include <string.h>
#define max(a,b) (a)>(b)?(a):(b)
const int N = 50;
const int M = 5;

int n, g[N][M], dp[N][N][N][N];

void init() {
	memset(dp, -1, sizeof(dp));
	memset(g, 0, sizeof(g));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < 4; j++) 
			scanf("%d", &g[i][j]);
}

int solve(int num[], int rec[], int cnt) {
	int& ans = dp[num[0]][num[1]][num[2]][num[3]];
	if (ans > -1) return ans;
	ans = 0;
	if (cnt == 5) return ans;

	for (int i = 0; i < 4; i++) {
		if (num[i] == n) continue;
		int t = g[num[i]][i];
		if (rec[t]) {
			rec[t] = 0, num[i]++;
			ans = max(ans, solve(num, rec, cnt - 1) + 1);
			rec[t] = 1, num[i]--;
		}
		else {
			rec[t] = 1, num[i]++;
			ans = max(ans, solve(num, rec, cnt + 1));
			rec[t] = 0, num[i]--;
		}
	}
	return ans;
}

int main() {
	while (scanf("%d", &n), n) {
		init();

		int num[M], rec[N];
		memset(rec, 0, sizeof(rec));
		memset(num, 0, sizeof(num));

		printf("%d\n", solve(num, rec, 0));
	}
	return 0;
}
