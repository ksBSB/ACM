#include <stdio.h>
#include <string.h>
const int N = 105;
const int MAX = 10005;

int x[MAX], y[MAX];
int g[N][N], sum[N][N];
int n, cut, k, dp[N][N], pace[N][N];

void init() {
	memset(g, 0, sizeof(g));
	for (int i = 0; i < n; i++)
		scanf("%d%d", &x[i], &y[i]);
	int l[N];
	scanf("%d", &k);
	for (int i = 0; i < k; i++)
		scanf("%d", &l[i]);
	scanf("%d", &cut);

	for (int i = 0; i < n; i++) {
		int j;
		for (j = 1; j < k; j++)
			if (x[i] < l[j]) break;
		g[y[i] + 1][j] = 1;
	}

	for (int i = 1; i < N; i++)
		for (int j = 1; j < k; j++)
			sum[i][j] = sum[i - 1][j] + g[i][j];
		
	memset(dp, -1, sizeof(dp));
}

int solve(int top, int cnt) {
	int& ans = dp[top][cnt];
	if (ans > -1) return ans;
	int& rec = pace[top][cnt];
	ans = 0;
	rec = top + 1;

	if (cnt == 0) {
		for (int i = 1; i < k; i++)
			if (sum[100][i] - sum[top][i]) ans++;
		rec = 100;
		return ans;
	}

	for (int i = top + 1; i <= 100 - cnt; i++) {
		int num = 0;
		for (int j = 1; j < k; j++)
			if (sum[i][j] - sum[top][j]) num++;
		num += solve(i, cnt - 1);
		if (num > ans) {
			ans = num;
			rec = i;
		}
	}
	return ans;
}

void put(int cur, int cnt) {
	printf(" %d", cur);
	if (cnt <  0) return ;
	put(pace[cur][cnt], cnt - 1);
}

int main () {
	while (scanf("%d", &n), n > -1) {
		init();
		solve(1, cut - 2);
		printf("%d", cut);
		put(1, cut - 2);
		printf("\n");
	}
	return 0;
}
