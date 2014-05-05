#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 205;
const int INF = 0x3f3f3f3f;

struct car {
	int s, t;
}A[N], B[N];

int n, ca, cb, dp[N][N][2];

void init () {
	scanf("%d%*c", &n);
	ca = cb = 0;
	char ch[N];
	for (int i = 0; i < n; i++) {
		scanf("%s", ch);
		if (ch[0] == 'A') {
			ca++;
			scanf("%d%d", &A[ca].s, &A[ca].t);
		} else {
			cb++;
			scanf("%d%d", &B[cb].s, &B[cb].t);
		}
	}
}

int solve () {
	memset(dp, INF, sizeof(dp));
	dp[0][0][0] = dp[0][0][1] = 0;
	for (int i = 0; i <= ca; i++) {
		for (int j = 0; j <= cb; j++) {
			int s = dp[i][j][0], end = 0;
			for (int k = i+1; k <= ca; k++) {
				s = max(s, A[k].s);
				end = max(s + A[k].t, end);
				dp[k][j][1] = min(dp[k][j][1], end);
				s += 10; end += 10;
			}

			s = dp[i][j][1]; end = 0;
			for (int k = j + 1; k <= cb; k++) {
				s = max(s, B[k].s);
				end = max(s + B[k].t, end);
				dp[i][k][0] = min(dp[i][k][0], end);
				s += 10; end += 10;
			}
		}
	}
	return min(dp[ca][cb][0], dp[ca][cb][1]);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init ();
		printf("%d\n", solve () );
	}
	return 0;
}
