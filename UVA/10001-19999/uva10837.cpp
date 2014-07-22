#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxp = 1e4;
const int INF = 0x3f3f3f3f;

int ans;
int np, vis[maxp+5], pri[maxp+5];
int nf, fact[maxp+5], v[maxp+5];

void prime_table (int n) {
	np = 0;
	for (int i = 2; i <= n; i++) {
		if (vis[i])
			continue;
		
		pri[np++] = i;
		for (int j = i * i; j <= n; j += i)
			vis[j] = 1;
	}
}

void get_fact (int n) {
	nf = 0;

	for (int i = 0; i < np && (pri[i]-1) * (pri[i]-1) <= n; i++) {
		if (n % (pri[i]-1) == 0)
			fact[nf++] = pri[i];
	}
}

bool judge (int n) {
	if (n == 2)
		return true;
	for (int i = 0; i < np && pri[i] * pri[i] <= n; i++)
		if (n % pri[i] == 0)
			return false;

	for (int i = 0; i < nf; i++)
		if (v[i] && fact[i] == n)
			return false;
	return true;
}

void dfs (int ret, int cur, int d) {
	if (d == nf) {
		if (judge(cur+1)) {

			if (cur == 1)
				cur = 0;

			ans = min(ans, ret * (cur+1));
		}
		return;
	}

	dfs(ret, cur, d+1);
	if (cur % (fact[d]-1) == 0) {
		v[d] = 1;
		ret *= fact[d];
		cur /= (fact[d]-1);

		while (true) {
			dfs(ret, cur, d+1);

			if (cur % fact[d])
				return;
			ret *= fact[d];
			cur /= fact[d];
		}
		v[d] = 0;
	}
}

int solve (int n) {
	ans = INF;
	get_fact(n);
	memset(v, 0, sizeof(v));
	dfs(1, n, 0);
	return ans;
}

int main () {
	prime_table(maxp);
	int cas = 1, n;
	while (scanf("%d", &n) == 1 && n) {
		printf("Case %d: %d %d\n", cas++, n, solve(n));
	}
	return 0;
}
