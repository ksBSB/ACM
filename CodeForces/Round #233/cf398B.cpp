#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 2005;

int n, m, r, l, x[N], y[N];
double dp[N][N];

void init () {
	memset(x, 0, sizeof(x));
	memset(y, 0, sizeof(y));

	scanf("%d%d", &n, &m);
	int a, b;
	r = l = n;

	for (int i = 0; i < m; i++) {
		scanf("%d%d", &a, &b);
		if (x[a] == 0) r--;
		if (y[b] == 0) l--;
		x[a]++; y[b]++;
	}
}

double solve () {
	dp[0][0] = 0;

	for (int i = 1; i <= n; i++) {
		dp[i][0] = dp[i-1][0] + n*1.0/i;
		dp[0][i] = dp[0][i-1] + n*1.0/i;
	}

	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= l; j++) {
			dp[i][j] = n * n;
			dp[i][j] += i * j * dp[i-1][j-1];
			dp[i][j] += i * (n-j) * dp[i-1][j];
			dp[i][j] += (n-i) * j * dp[i][j-1];

			dp[i][j] /= (n*n - (n-i)*(n-j));
		}
	}
	return dp[r][l];
}

int main () {
	init ();
	printf("%.10lf\n", solve () );
	return 0;
}
