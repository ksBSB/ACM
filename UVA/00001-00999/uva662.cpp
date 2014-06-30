#include <stdio.h>
#include <string.h>
#define min(a,b) (a)<(b)?(a):(b)
const int N = 205;
const int K = 35;
const int MAX = 1 << 30;
int n, m, dp[K][N], dis[N][N], sta[N], rec[K][N];

void init() {
	int sum[N];
	memset(sum, 0, sizeof(sum));
	for (int i = 1; i <= n; i++) {
		scanf("%d", &sta[i]);
		sum[i] = sum[i - 1] + sta[i];
	}

	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j++) {
			int mid = (i + j) / 2;
			dis[i][j] = (mid - i) * sta[mid] - sum[mid - 1] + sum[i - 1];
			dis[i][j] += sum[j] - sum[mid] - (j - mid) * sta[mid];
		}
	}
}

int solve() {
	memset(dp, -1, sizeof(dp));
	memset(rec, 0, sizeof(rec));
	for (int i = 0; i <= n; i++)
		dp[0][i] = MAX;
	for (int k = 1; k <= m; k++) {
		for (int i = k; i <= n; i++) {
			dp[k][i] = dis[1][i];
			for (int j = k - 1; j < i; j++) {
				if (dp[k - 1][j] + dis[j + 1][i] < dp[k][i]) {
					dp[k][i] = dp[k - 1][j] + dis[j + 1][i];
					rec[k][i] = j;
				}
			}
		}
	}
	return dp[m][n];
}

void put(int cas, int x, int y) {
	int mid = (x + y) / 2;
	printf("Depot %d at restaurant %d serves ", cas, mid);
	if (x == y)
		printf("restaurant %d\n", x);
	else
		printf("restaurants %d to %d\n", x, y);
}

void print(int k, int x) {
	if (k > 1)
		print(k - 1, rec[k][x]);
	put(k, rec[k][x] + 1, x);
}

int main() {
	int cas = 1;
	while (scanf("%d%d", &n, &m), n || m) {
		init();

		printf("Chain %d\n", cas++);
		int ans = solve();
		print(m, n);
		printf("Total distance sum = %d\n\n", ans);
	}
	return 0;
}
