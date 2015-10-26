#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
const int maxn = 5 * 1e8;
const int maxm = 3 * 1e4;
typedef pair<int,int> pii;

int N, M, C, P[maxm];
bool vis[maxm];
map<int, pii> dp[maxm];

void init () {
	C = 0;
	P[C++] = 1;
	memset(vis, false, sizeof(vis));
	for (int i = 2; i * i <= maxn; i++) {
		if (vis[i]) continue;
		P[C++] = i;
		for (int j = i + i; j * j <= maxn; j += i)
			vis[j] = true;
	}
}

int pow_mod(int x, int n) {
	int ret = 1;
	while (n) {
		if (n&1) ret = ret * x % M;
		x = x * x % M;
		n >>= 1;
	}
	return ret;
}

int fac(int n) {
	int t = n / M, k = n % M, ret = 1;
	for (int i = 1; i < M; i++)
		ret = ret * i % M;
	ret = pow_mod(ret, t);

	for (int i = 1; i <= k; i++)
		ret = ret * i % M;
	return ret;
}

int solve (int i, int v) {
	if (dp[i].count(v)) return dp[i][v].first;

	if (P[i] * P[i] > v || P[i] == M) {
		int tmp = solve(i-1, v);
		dp[i][v] = dp[i-1][v];
		return tmp;
	}
	if (i == 0) {
		int tmp = fac(v);
		dp[i][v] = make_pair(tmp, v - v / M);
		return tmp;
	}

	int ret = solve(i-1, v) * solve(i-1, P[i-1]) % M;
	int div = solve(i-1, v / P[i]);
	int c = dp[i-1][v/P[i]].second - dp[i-1][P[i-1]].second;
	int pri = P[i] == M ? 1 : pow_mod(P[i], c);

	ret = ret * pow_mod(div * pri % M, M-2) % M;

	dp[i][v] = make_pair(ret, dp[i-1][v].second - c);
	return ret;
}

int main () {
	init();
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%d%d", &N, &M);
		int m = sqrt(N), n = 0;
		while (P[n] < m && n < C - 1) n++;
		for (int i = 0; i <= n; i++) dp[i].clear();
		printf("Case #%d: %d\n", kcas, solve(n, N));
	}
	return 0;
}
