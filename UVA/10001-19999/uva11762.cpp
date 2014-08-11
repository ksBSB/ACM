#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e6;

int np, prime[maxn+5], vis[maxn+5];
double dp[maxn];

void prime_table(int n) {
	np = 0;
	memset(vis, 0, sizeof(vis));
	
	for (int i = 2; i <= maxn; i++) {
		if (vis[i])
			continue;
		prime[np++] = i;
		for (int j = i * 2; j <= maxn; j += i)
			vis[j] = 1;
	}
}

double dfs (int n) {
	if (vis[n])
		return dp[n];

	if (n == 1)
		return dp[n] = 0;

	double& ans = dp[n];
	int g = 0, p = 0;
	ans = 0;

	for (int i = 0; i < np && prime[i] <= n; i++) {
		p++;
		if (n % prime[i] == 0) {
			g++;
			ans += dfs(n / prime[i]);
		}
	}
	return ans = (ans + p) / g;
}

int main () {
	prime_table(maxn);
	memset(vis, 0, sizeof(vis));

	int cas, n;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%d", &n);
		printf("Case %d: %.10lf\n", kcas, dfs(n));
	}
	return 0;
}
