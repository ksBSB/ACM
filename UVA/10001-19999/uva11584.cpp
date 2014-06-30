#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 1005;
const int INF = 0x3f3f3f3f;

int n, dp[N];
char str[N];

bool judge(int l, int r) {
	while (l <= r) {
		if (str[l] != str[r]) return false;
		l++; r--;
	}
	return true;
}

int solve () {
	memset(dp, INF, sizeof(dp));
	dp[0] = 0;

	scanf("%s", str+1);
	n = strlen(str+1);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			if (judge(j, i))
				dp[i] = min(dp[i], dp[j-1]+1);
		}
	}
	return dp[n];
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		printf("%d\n", solve());
	}
	return 0;
}
