#include <stdio.h>
#include <string.h>
#define min(a,b) (a) < (b) ? (a) : (b)
const int MAX = 1 << 30;

int vis[705][205][105], dp[705][205][105];

int solve(int c, int n1, int n5, int n10) {
	int&cnt = dp[n1][n5][n10];
	int& flag = vis[n1][n5][n10];
	if (flag) return cnt;
	else if (c == 0) {
		flag = 1;
		cnt = 0;
		return cnt;
	}
	else {
		cnt = MAX;
		if (n1 >= 8) cnt = min(cnt, solve(c - 1, n1 - 8, n5,  n10) + 8);
		if (n5 >= 1 && n1 >= 3) cnt = min(cnt, solve(c - 1, n1 - 3, n5 - 1, n10) + 4);
		if (n5 >= 2) cnt = min(cnt, solve(c - 1, n1 + 2, n5 - 2, n10) + 2);
		if (n10 >= 1) cnt = min(cnt, solve(c - 1, n1 + 2, n5, n10 - 1) + 1);
		if (n10 >= 1 && n1 >= 3) cnt = min(cnt, solve(c - 1, n1 - 3, n5 + 1, n10 - 1) + 4);
		flag = 1;
		return cnt;
	}
}

int main() {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		int c, n1, n5, n10;
		scanf("%d%d%d%d", &c, &n1, &n5, &n10);
		memset(vis, 0, sizeof(vis));
		printf("%d\n", solve(c, n1, n5, n10));
	}
	return 0;
}
