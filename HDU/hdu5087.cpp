#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1005;

int N, A[maxn], dp[maxn][2];

void update(int u, int d) {
	dp[u][0] = max(dp[u][0], d);
	if (dp[u][0] > dp[u][1])
		swap(dp[u][0], dp[u][1]);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &N);
		memset(dp, 0, sizeof(dp));

		for (int i = 1; i <= N; i++)
			scanf("%d", &A[i]);

		int fans = 0, sans = 0;
		dp[0][0] = -maxn;
		for (int i = 1; i <= N; i++) {
			for (int j = 0; j < i; j++) {
				if (A[i] > A[j]) {
					update(i, dp[j][0] + 1);
					update(i, dp[j][1] + 1);
				}
			}

			for (int j = 0; j < 2; j++) {
				
				sans = max(sans, dp[i][j]);
				if (sans > fans)
					swap(sans, fans);
			}
		}
		printf("%d\n", sans);
	}
	return 0;
}
