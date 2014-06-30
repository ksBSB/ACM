#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 5005;
const int M = 55;
const int INF = 0x3f3f3f3f;

char s[M], e[N];
int n, m, dp[N][M];

void init () {
	scanf("%s%s", s+1, e+1);
	n = strlen(e+1);
	m = strlen(s+1);
}

bool judge (int k) {
	memset(dp, INF, sizeof(dp));

	dp[0][0] = 0;
	for (int i = 0; i <= n; i++) {

		if (dp[i][m] <= k)
			dp[i][0] = 0;

		for (int j = 0; j <= m; j++) {
			if (dp[i][j] > k)
				continue;

			dp[i+1][j+1] = min(dp[i+1][j+1], dp[i][j] + (e[i+1] == s[j+1] ? 0 : 1));
			dp[i+1][j] = min(dp[i+1][j], dp[i][j]+1);
			dp[i][j+1] = min(dp[i][j+1], dp[i][j]+1);
		}
	}
	return dp[n][m] <= k;
}

int search() {
	int l = 0, r = m;
	while (l < r) {
		int mid = (l + r) / 2;

		if (judge(mid))
			r = mid;
		else
			l = mid + 1;
	}
	return l;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init ();
		printf("%d\n", search());
	}
	return 0;
}
