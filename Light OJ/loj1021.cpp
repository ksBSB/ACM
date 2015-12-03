#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 25;
const int maxs = 1<<17;
typedef long long ll;

int base, K;
char s[maxn];
ll dp[maxs][maxn];

int idx(char ch) {
	if (ch >= '0' && ch <= '9') return ch - '0';
	else return ch - 'A' + 10;
}

ll solve () {
	memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;
	int n = strlen(s);
	for (int i = 0; i < (1<<n); i++) {
		for (int j = 0; j < n; j++) if ((i&(1<<j)) == 0) {
			for (int k = 0; k < K; k++) {
				int v = (k * base + idx(s[j])) % K;
				dp[i|(1<<j)][v] += dp[i][k];
			}
		}
	}
	return dp[(1<<n)-1][0];
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%d%d%s", &base, &K, s);
		printf("Case %d: %lld\n", kcas, solve());
	}
	return 0;
}
