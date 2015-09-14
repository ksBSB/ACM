#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 2005;
const int inf = 0x3f3f3f3f;

int N, M, dp[maxn];

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d", &M, &N);
		memset(dp, 0, sizeof(dp));

		int w, a, b;
		for (int i = 0; i < N; i++) {
			scanf("%d%d%d", &w, &a, &b);
			for (int j = M-w; j >= 0; j--)
				dp[j+w] = max(dp[j+w], dp[j] + a + b);
			for (int j = 0; j + w <= M; j++)
				dp[j+w] = max(dp[j+w], dp[j] + a);
		}
		int ans = 0;
		for (int i = 0; i <= M; i++)
			ans = max(ans, dp[i]);
		printf("%d\n", ans);
	}
	return 0;
}
