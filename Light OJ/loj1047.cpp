#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 30;
const int inf = 0x3f3f3f3f;

int N, dp[maxn][3];

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%d", &N);
		for (int i = 1; i <= N; i++) {
			for (int j = 0; j < 3; j++)
				scanf("%d", &dp[i][j]);
		}
		for (int i = 2; i <= N; i++) {
			for (int j = 0; j < 3; j++) {
				int s = inf;
				for (int k = 0; k < 3; k++) if (j != k)
					s = min(s, dp[i-1][k]);
				dp[i][j] += s;
			}
		}
		int ans = inf;
		for (int i = 0; i < 3; i++)
			ans = min (ans, dp[N][i]);
		printf("Case %d: %d\n", kcas, ans);
	}
	return 0;
}
