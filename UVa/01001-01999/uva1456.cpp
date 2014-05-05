#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stdlib.h>

using namespace std;
const int N = 105;
const double INF = 0x3f3f3f3f3f3f3f3f;

int n, w, sum, s[N], p[N];
double dp[N][N];

bool cmp(const int& a, const int& b) {
	return a > b;
}

void init () {
	sum = s[0] = 0;
	scanf("%d%d", &n, &w);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &p[i]);
		sum += p[i];
	}
	sort(p+1, p+n+1, cmp);
	for (int i = 1; i <= n; i++)
		s[i] = s[i-1] + p[i];
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= w; j++) dp[i][j] = INF;
}

double solve () {
	dp[0][0] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i && j <= w; j++) {
			dp[i][j] = INF;
			for (int k = j-1; k < i; k++)
				dp[i][j] = min(dp[i][j], dp[k][j-1] + (s[i]-s[k])/(sum*1.0)*i);
		}
	}
	return dp[n][w];
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%.4lf\n", solve());
	}
	return 0;
}
