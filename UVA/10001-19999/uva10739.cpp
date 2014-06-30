#include <stdio.h>
#include <string.h>
const int N = 1005;
int min(int a, int b) { return a < b ? a : b; }

int len, dp[N][N];
char str[N];

void solve() {
    len = strlen(str);
    memset(dp, 0, sizeof(dp));
    for (int i = len - 1; i >= 0; i--) {
	for (int j = i + 1; j < len; j++) {
	    if (str[i] == str[j])
		dp[i][j] = dp[i + 1][j - 1];
	    else
		dp[i][j] = min( min(dp[i + 1][j], dp[i][j - 1]), dp[i + 1][j - 1]) + 1;
	}
    }
}

int main() {
    int cas, t = 1;
    scanf("%d", &cas); 
    while (cas--) {
	scanf("%s", str);
	solve();
	printf("Case %d: %d\n", t++, dp[0][len - 1]);
    }
    return 0;
}
