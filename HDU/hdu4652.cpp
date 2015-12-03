#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 1e6 + 5;

/* 
 * k = 0, 设dp[i]表示连续出现i的一样的次数期望
 * 设xi = dp[i] - dp[i-1]
 * xi = 1 + (m-1)/m * (dp[i-1]-1+xi)
 * xi = m + (m-1) * (dp[i-1]-1)
 * dp[i] = dp[i-1] + m + (m-1) * (dp[i-1] - 1)
 * dp[i] = dp[i-1] * m + 1;
 * dp[i] + 1/(m-1) = m * (dp[i-1] + 1/(m-1))
 *
 * 令a[i] = dp[i] + 1/(m-1)
 * 则有a[i] = m * a[i-1]
 *
 *
 * k = 1, 设dp[i]表示连续出现i个两两不相同的次数期望
 * 设xi = dp[i] - dp[i-1], s[i] = dp[1] + ... + dp[i]
 * xi = 1 + (i-1)/m * xi + ((i-1)*dp[i-1] - s[i-1])/m
 * xi = (m + (i-1)*dp[i-1] - s[i-1]) / (m-i+1)
 * dp[i] = dp[i-1] + xi
 * dp[i] = (m * dp[i-1] + m - s[i-1]) / (m-i+1)
 */

int main () {
	int cas;
	while (scanf("%d", &cas) == 1) {
		while (cas--) {
			int k, m, n;
			double ans = 0;
			scanf("%d%d%d", &k, &m, &n);
			if (k) {
				double sum = 0;
				for (int i = 1; i <= n; i++) {
					ans = (m * ans + m - sum) / (m - i + 1);
					sum += ans;
				}
			} else {
				if (m == 1) ans = n;
				else ans = (pow(m, n) - 1) / (m-1);
			}
			printf("%.8lf\n", ans);
		}
	}
	return 0;
}

