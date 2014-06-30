#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;
const int N = 1005;
const int INF = 0x3f3f3f3f;
int n, p, d[N], dp[N][N];

int dis (int a, int b) {
	int tmp = abs(d[a] - d[b]);
	return min(tmp, 360 - tmp);
}

void init () {
	int a;

	scanf("%d", &n);
	d[1] = 0;
	for (int i = 2; i <= n + 1; i++) {
		scanf("%d%d", &a, &d[i]);

		if (i == n + 1)
			p = a;
	}
	dp[2][1] = dis(1, 2);
}

int solve () {

	for (int i = 3; i <= n + 1; i++) {  
		dp[i][i-1] = INF;  

		for (int j = 1; j < i-1; j++) {  
			dp[i][i-1] = min(dp[i][i-1], dp[i-1][j] + dis(i, j));  
			dp[i][j] = dp[i-1][j] + dis(i, i-1);  
		}  
	}  

	int ans = INF;  
	for (int i = 1; i <= n; i++)  
		ans = min(ans, dp[n+1][i] + dis(n+1, i));  
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		init();
		printf("%d\n", solve() + p * 800 + 10 * n);
	}
	return 0;
}
