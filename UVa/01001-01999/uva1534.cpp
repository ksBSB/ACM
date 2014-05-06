#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int N = 505;

int n, m;
double cn[N], cm[N], dp[N][N];

void init () {
	scanf("%d%d", &n, &m);

	for (int i = 0; i < n; i++)
		scanf("%lf", &cn[i]);
	for (int i = 0; i < m; i++)
		scanf("%lf", &cm[i]);

	sort(cn, cn + n);
	sort(cm, cm + m);

	if (n > m) {
		double tmp[N];
		memcpy(tmp, cm, m*sizeof(double));
		memcpy(cm, cn, n*sizeof(double));
		memcpy(cn, tmp, m*sizeof(double));
		swap(n, m);
	}
}

double solve () {

	dp[0][0] = fabs(cn[0] - cm[0]);
	for (int i = 1; i < m; i++)
		dp[0][i] = min (fabs(cn[0]-cm[i]), dp[0][i-1]);

	for (int i = 1; i < n; i++) {
		dp[i][i] = dp[i-1][i-1] + fabs(cn[i]-cm[i]);

		for (int j = i+1; j < m; j++)
			dp[i][j] = min (dp[i-1][j-1] + fabs(cn[i] - cm[j]), dp[i][j-1]);
	}
	return dp[n-1][m-1];
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init ();
		printf("%.1lf\n", solve());
	}
	return 0;
}
