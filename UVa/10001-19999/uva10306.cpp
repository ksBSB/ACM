#include <stdio.h>
#include <string.h>
const int N = 305;

struct coin{
    int x;
    int y;
}val[50];
int n, s, S, dp[N][N];

void read() {
   memset(val, 0, sizeof(val));
   scanf("%d%d", &n, &s);
   S = s * s;
   for (int i = 0; i < n; i++)
       scanf("%d%d", &val[i].x, &val[i].y);
}

int solve() {
    int cnt = 1 << 30;
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (int k = 0; k < n; k++) {
	for (int i = 0; i <= s; i++) {
	    for (int j = 0; j <= s; j++) {
		if (dp[i][j]) {
		    int p = i + val[k].x, q = j + val[k].y;
		    if (p > s || q > s) break;
		    if (dp[p][q] == 0 || dp[i][j] + 1 < dp[p][q])
			dp[p][q] = dp[i][j] + 1;
		    if (p * p + q * q == S && dp[p][q] < cnt)
			cnt = dp[p][q];
		}
	    }
	}
    }
    if (cnt == 1 << 30) return 0;
    else return cnt;
}

int main() {
    int cas;
    scanf("%d", &cas);
    while (cas--) {
	read();
	int ans = solve();
	if (ans)
	    printf("%d\n", ans - 1);
	else
	    printf("not possible\n");
    }
    return 0;
}
