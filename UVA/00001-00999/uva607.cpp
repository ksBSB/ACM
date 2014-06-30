#include <stdio.h>
#include <string.h>
const int N = 1005;
const int MAX = 1 << 30;
int min(int a, int b) { return a < b ? a : b; }

int n, l, c, cnt, t[N], dp[N][N], vis[N][N];

void handle() {
	memset(vis, 0, sizeof(vis));
	cnt = 0;
	int sum = 0;
	for (int i = 1; i <= n; i++) {
		sum += t[i];
		if (sum > l) {
			sum = t[i];
			cnt++;
		}
	}
}

int get(int tmp) {
	if (tmp == 0) return 0;
	else if (tmp <= 10) return -c;
	else return (tmp - 10) * (tmp - 10);
}

int solve(int x, int y) {
	if (vis[x][y]) return dp[x][y];
	int& ans = dp[x][y];
	
	if (x == 0)
		return y ? MAX : 0;
	else {
		ans = MAX;
		int sum = 0;
		for (int i = y; i > 0; i--) {
			sum += t[i];
			if (sum > l) break;
			int now = solve(x - 1, i - 1);
			if (now != MAX)
				ans = min(now + get(l - sum), ans);
			
		}
		vis[x][y] = 1;
		return ans;
	}
}

int main() {
	int cas = 0;
	while (scanf("%d", &n), n) {
		scanf("%d%d", &l, &c);
		for (int i = 1; i <= n; i++)
			scanf("%d", &t[i]);

		handle();

		if (cas) printf("\n");	
		printf("Case %d:\n", ++cas);
		printf("Minimum number of lectures: %d\n", ++cnt);
		printf("Total dissatisfaction index: %d\n", solve(cnt, n));
	}
	return 0;
}
