#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 205;
const int INF = 0x3f3f3f3f;

int dp[N][N];
char str[N];

bool judge(int l, int r, int k) {
	if ((r-l+1)%k) return false;

	for (int i = 0; i < k; i++) {
		for (int j = l+i+k; j <= r; j += k) if (str[l+i] != str[j])
			return false;
	}		
	return true;
}

int catnum(int x) {
	int ans = 0;
	while (x) {
		ans++;
		x /= 10;
	}
	return ans;
}

int solve () {

	scanf("%s", str+1);
	int n = strlen(str+1);

	memset(dp, INF, sizeof(dp));
	for (int i = 0; i <= n; i++) dp[i][i] = 1;

	for (int i = n; i; i--) {
		for (int j = i; j <= n; j++) {
			for (int k = i; k < j; k++) 
				dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j]);

			int t = j - i + 1;
			for (int k = 1; k < t; k++) if (judge(i, j, k)) {
				dp[i][j] = min(dp[i][j], dp[i][i+k-1] + 2 + catnum(t/k));
			}
		}
	}
	return dp[1][n];
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		printf("%d\n", solve());	
	}
	return 0;
}
