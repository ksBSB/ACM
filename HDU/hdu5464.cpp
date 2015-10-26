#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1005;
const int mod = 1e9 + 7;

int N, P, dp[maxn], tmp[maxn];

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d", &N, &P);
		memset(dp, 0, sizeof(dp));
		dp[0] = 1;
		int x;
		for (int i = 1; i <= N; i++) {
			scanf("%d", &x);
			x = (x % P + P) % P;
			memcpy(tmp, dp, sizeof(dp));
			for (int j = 0; j < P; j++)
				dp[(j+x)%P] = (dp[(j+x)%P] + tmp[j]) % mod;
		}
		printf("%d\n", dp[0]);
	}
	return 0;
}
