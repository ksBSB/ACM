#include <stdio.h>
#include <string.h>
#define min(a,b) (a)<(b)?(a):(b)
const int INF = 1 << 30;
const int N = 20;
const int MAX = 2000000;

struct state {
	int over;
	int value;
}g[N][N];
int n, m, dp[MAX], vis[MAX], cnt[N];

void init() {
	int a;
	memset(dp, 0, sizeof(dp));
	memset(cnt, 0, sizeof(cnt));
	memset(vis, 0, sizeof(vis));

	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d%d", &g[i][j].over, &g[i][j].value);
			

	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf("%d", &a);
		cnt[a]++;
	}
	/*
	for (int i = 1; i <= n; i++)
		printf("%d:%d\n", i, cnt[i]);
		*/
	char ch[N];
	scanf("%s", ch);
}

int hash(int a[]) {
	int sum = 0, flag = 0;
	for (int i = 1; i <= n; i++) {
		if (a[i] == 1) flag++;
		else if (a[i] > 1) flag = 2;
		sum = sum * 11 + a[i];
	}
	if (flag == 1) sum = 0;
	return sum;
}

int solve() {
	int k = hash(cnt);
	if (k == 0) return 0;
	else if (vis[k]) return dp[k];

	int& ans = dp[k];
	ans = INF;
	for (int i = 1; i <= n; i++) {
		if (cnt[i]) {
			cnt[i]--;
			for (int j = 1; j <= n; j++) {
				if (cnt[j]) {
					cnt[j]--;
					cnt[g[i][j].over]++;
					ans = min(solve() + g[i][j].value, ans);
					cnt[j]++;
					cnt[g[i][j].over]--;
				}
			}
			cnt[i]++;
		}
	}
	vis[k] = 1;
	return ans;
}

int main() {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}
