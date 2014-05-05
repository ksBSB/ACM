#include <stdio.h>
#include <string.h>
const int N = 1005;

int n, dp[N][N], rec[N][N];
char str[N];

int solve() {
    n = strlen(str);
    memset(dp, 0, sizeof(dp));
    memset(rec, 0, sizeof(rec));
    
    for (int i = n - 1; i >= 0; i--) {
	for (int j = i + 1; j < n; j++) {
	    if (str[i] == str[j])
		dp[i][j] = dp[i + 1][j - 1];
	    else {
		if (dp[i + 1][j] > dp[i][j - 1]) {
		    dp[i][j] = dp[i][j - 1] + 1;
		    rec[i][j] = 1;
		}
		else {
		    dp[i][j] = dp[i + 1][j] + 1;
		    rec[i][j] = -1;
		}
	    }
	}
    }
    return dp[0][n - 1];
}

void print(int a, int b) {
    if (a > b)	return;
//    printf("%d!\n", rec[a][b]);
    if (a == b)
	printf("%c", str[a]);
    else if (rec[a][b] == 0) {
	printf("%c", str[a]);
	print(a + 1, b - 1);
	printf("%c", str[a]);
    }
    else if (rec[a][b] == 1) {
	printf("%c", str[b]);
	print(a, b - 1);
	printf("%c", str[b]);
    }
    else {
	printf("%c", str[a]);
	print(a + 1, b);
	printf("%c", str[a]);
    }
}

int main() {
    while (gets(str)) {
	printf("%d ", solve());
	print(0, n - 1);
	printf("\n");
    }
    return 0;
}
