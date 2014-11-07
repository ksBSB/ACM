#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1e6+5;

int N, a[maxn];
ll dp[maxn][2];

int main () {
	scanf("%d%d", &N, &a[1]);

	for (int i = 2; i <= N; i++) {
		scanf("%d", &a[i]);
		if (a[i] > a[i-1]) {
			dp[i][0] = max(dp[i-1][1], dp[i-1][0] + a[i] - a[i-1]);
			dp[i][1] = max(dp[i-1][1], dp[i-1][0]);
		} else {
			dp[i][1] = max(dp[i-1][0], dp[i-1][1] + a[i-1] - a[i]);
			dp[i][0] = max(dp[i-1][0], dp[i-1][1]);
		}
	}
	printf("%lld\n", max(dp[N][0], dp[N][1]));
	return 0;
}
