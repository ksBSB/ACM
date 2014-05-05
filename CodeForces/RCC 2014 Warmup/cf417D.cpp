#include <cstdio>
#include <cstring>
#include <set>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
const int N = (1<<20)+5;
const int M = 105;
const ll INF = 0x3f3f3f3f3f3f3f3f;

struct state {
	int s;
	ll k, val;
}p[M];
int n, m;
ll b, dp[N];

bool cmp (const state& a, const state& b) {
	return a.k < b.k;
}

void init () {
	memset(dp, -1, sizeof(dp));

	scanf("%d%d", &n, &m);
	cin >> b;

	int t, a;
	for (int i = 0; i < n; i++) {
		cin >> p[i].val >> p[i].k >> t;
		p[i].s = 0;
		for (int j = 0; j < t; j++) {
			scanf("%d", &a);
			p[i].s |= (1<<(a-1));
		}
	}
	sort(p, p + n, cmp);
}

ll solve () {
	dp[0] = 0;

	int t = (1<<m)-1;
	ll ans = INF;
	for (int i = 0; i < n; i++) {

		for (int j = 0; j <= t; j++) {
			if (dp[j] == -1) continue;

			int u = p[i].s | j;

			if (dp[u] == -1)
				dp[u] = p[i].val + dp[j];
			else 
				dp[u] = min(dp[u], p[i].val + dp[j]);
		}

		if (dp[t] != -1)
			ans = min(ans, dp[t] + p[i].k * b);
	}

	return ans == INF ? -1 : ans;
}

int main () {
	init ();
	cout << solve() << endl;
	return 0;
}
