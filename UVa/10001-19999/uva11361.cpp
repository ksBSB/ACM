#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 15;
const int M = 105;

int a, b, k, n, d[N];
int dp[N][M][M];

void cat(int u) {
	n = 1;
	memset(d, 0, sizeof(d));
	while (u) {
		d[n++] = u%10;
		u /= 10;
	}

	for (int i = 1; i <= n/2; i++)
		swap(d[i], d[n-i+1]);
}

int solve (int u) {
	if (u == 0)
		return 1;

	cat(u);
	memset(dp, 0, sizeof(dp));
	int p = 0, q = 0;

	for (int i = 1; i <= n; i++) {

		for (int j = 0; j <= k; j++) {
			for (int t = 0; t <= k; t++) {
				
				for (int x = 0; x < 10; x++)
					dp[i][(j*10+x)%k][(t+x)%k] += dp[i-1][j][t];
			}
		}

		for (int j = 0; j < d[i]; j++)
			dp[i][(p*10+j)%k][(q + j)%k]++;

		p = (p*10+d[i])%k;
		q = (q+d[i])%k;
	}

	if (p == 0 && q == 0)
		dp[n][0][0]++;
	return dp[n][0][0];
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d%d", &a, &b, &k);
		if (k > 100)
			printf("0\n");
		else
			printf("%d\n", solve(b) - solve(a-1));
	}
	return 0;
}
