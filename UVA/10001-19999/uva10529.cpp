#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 1005;
const double INF = 0x3f3f3f3f3f3f3f;

int N;
double pl, pr, dp[maxn];

double solve () {
	double ac = 1 - pl - pr;

	for (int i = 1; i <= N; i++) {
		dp[i] = INF;
		for (int j = 0; j < i; j++) {
			double tmp = dp[i-j-1] * pl + dp[j] * pr;
			tmp = dp[j] + dp[i-j-1] + (tmp + 1) / ac;
			if (tmp < dp[i])
				dp[i] = tmp;
		}
	}
	return dp[N];
}

int main () {
	while (scanf("%d", &N) == 1 && N) {
		scanf("%lf%lf", &pl, &pr);
		printf("%.2lf\n", solve());
	}
	return 0;
}
