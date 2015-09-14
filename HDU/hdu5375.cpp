#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 200005;

char S[maxn];
int N, dp[maxn][2], W[maxn];

void init () {
	scanf("%s", S + 1);
	N = strlen(S + 1);
	for (int i = 1; i <= N; i++)
		scanf("%d", &W[i]);

}

int solve () {
	memset(dp, 0, sizeof(dp));

	if (S[1] == '0')
		dp[1][0] = 0, dp[1][1] = -1;
	else if (S[1] == '1')
		dp[1][0] = -1, dp[1][1] = W[1];
	else
		dp[1][0] = 0, dp[1][1] = W[1];

	for (int i = 2; i <= N; i++) {
		for (int j = 0; j <= 1; j++) {
			if (S[i] != '?' && S[i] != '0' + j) {
				dp[i][j] = -1;
				continue;
			}

			for (int k = 0; k <= 1; k++) {
				if (dp[i-1][k] == -1)
					continue;
				dp[i][j] = max(dp[i][j], dp[i-1][k] + (j^k) * W[i]);
			}
		}
		//printf("%d %d\n", dp[i][0], dp[i][1]);
	}

	return max(dp[N][0], dp[N][1]);
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init ();
		printf("Case #%d: %d\n", kcas, solve());
	}
	return 0;
}
