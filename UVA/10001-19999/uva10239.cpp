#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 1005;
const double INF = 0x3f3f3f3f3f3f3f3f;

int n, v[N];;
double W, h[N], w[N], dp[N];

double solve (int u) {
	if (u >= n+1) return 0;
	if (v[u]) return dp[u];

	double& ans = dp[u];
	v[u] = 1;
	ans = INF;

	double H = h[u], tmp = w[u];

	for (int i = u+1; i <= n+1; i++) {
		ans = min(ans, solve(i) + H);

		tmp = tmp + w[i];
		H = max(H, h[i]);
		if (tmp - W > 1e-9) break;
	}
	return ans;
}

int main () {
	while (scanf("%d%lf", &n, &W) == 2 && n + W) {

		memset(v, 0, sizeof(v));
		for (int i = 1; i <= n; i++) 
			scanf("%lf%lf", &h[i], &w[i]);
		printf("%.4lf\n", solve(1));
	}
	return 0;
}
