#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 25;
const int INF = 0x3f3f3f3f;
int n, f[N], s[N], dp[N][N][N][N][2];

void init () {
	memset(dp, -1, sizeof(dp));

	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &f[i]);
	for (int i = 1; i <= n; i++)
		scanf("%d", &s[i]);
}

int solve (int fl, int fr, int sl, int sr, int flag) {
	int& ans = dp[fl][fr][sl][sr][flag];
	if (fl > fr && sl > sr)
		return ans = 0;

	if (ans != -1)
		return ans;

	if (flag) {
		ans = 0;
		if (fl <= fr) {
			ans = max(ans, solve(fl+1, fr, sl, sr, 1-flag) + f[fl]);
			ans = max(ans, solve(fl, fr-1, sl, sr, 1-flag) + f[fr]);
		}

		if (sl <= sr) {
			ans = max(ans, solve(fl, fr, sl+1, sr, 1-flag) + s[sl]);
			ans = max(ans, solve(fl, fr, sl, sr-1, 1-flag) + s[sr]);
		}
	} else {
		ans = INF;
		if (fl <= fr) {
			ans = min(ans, solve(fl+1, fr, sl, sr, 1-flag));
			ans = min(ans, solve(fl, fr-1, sl, sr, 1-flag));
		}

		if (sl <= sr) {
			ans = min(ans, solve(fl, fr, sl+1, sr, 1-flag));
			ans = min(ans, solve(fl, fr, sl, sr-1, 1-flag));
		}
	}
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init ();
		printf("%d\n", solve(1, n, 1, n, 1));
	}
	return 0;
}
