#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = (1<<15) + 5;
const int maxm = 20;
const int inf = 0x3f3f3f3f;

int N, H[maxm], dp[maxn];
char ws[maxn][maxm], wp[maxm][maxm];

void init () {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &H[i]);
	for (int i = 0; i < N; i++)
		scanf("%s", wp[i]);

	for (int i = 0; i < N; i++)
		ws[0][i] = '1';

	for (int i = 1; i < (1<<N); i++) {
		int v = i, u;
		for (u = 0; u < N; u++) if (i&(1<<u)) {
			v -= (1<<u); break;
		}

		for (int j = 0; j < N; j++)
			ws[i][j] = max(ws[v][j], wp[u][j]);
	}
}

int solve () {
	dp[0] = 0;
	for (int i = 1; i < (1<<N); i++) {
		dp[i] = inf;
		for (int j = 0; j < N; j++) if (i&(1<<j)) {
			int v = i - (1<<j);
			int k = ws[v][j] - '0';
			dp[i] = min(dp[i], dp[v] + H[j] / k + (H[j] % k ? 1 : 0));
		}
	}
	return dp[(1<<N)-1];
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();
		printf("Case %d: %d\n", kcas, solve());
	}
	return 0;
}
