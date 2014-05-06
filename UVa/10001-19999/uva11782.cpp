#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = (1<<20)+5;
const int K = 25;
const int INF = 0x3f3f3f3f;
int n, k, dp[N][K];

void buildTree(int u, int d) {
	if (d > n)
		return;

	scanf("%d", &dp[u][1]);
	buildTree(u*2+1, d+1);
	buildTree(u*2+2, d+1);
}

int solve () {
	int t = (1<<(n+1))-2;
	for (int i = 2; i <= k; i++) {
		for (int j = t; j >= 0; j--) {
			int p = j*2+1;
			int q = j*2+2;

			dp[j][i] = dp[j][i-1];

			if (p > t || q > t) 
				continue;

			for (int x = 1; x < i; x++)
				dp[j][i] = max(dp[j][i], dp[p][x] + dp[q][i-x]);
		}
	}
	return dp[0][k];
}

int main () {
	while (scanf("%d", &n) == 1 && n != -1) {
		scanf("%d", &k);
		buildTree(0, 0);
		printf("%d\n", solve());
	}
	return 0;
}
