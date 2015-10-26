#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const int maxn = 1e5 + 5;
const int mod = 1e9 + 7;

int N, P[maxn];
vector<pii> G;

void init () {
	int l, r;
	scanf("%d", &N);
	G.clear();

	for (int i = 1; i <= N; i++) {
		scanf("%d%d", &l, &r);
		G.push_back(make_pair(l, 1));
		G.push_back(make_pair(r, -1));
	}
	sort(G.begin(), G.end());
}

int solve () {
	int c = 0, p = 0, n = G.size(), ret = 0;
	while (p < n) {
		c += G[p++].second;
		while (p < n && G[p].first == G[p-1].first)
			c += G[p++].second;
		if (p == n) break;

		int len = G[p].first - G[p-1].first;
		ret = (ret + 1LL * len * (P[c]-1) % mod * P[N-c] % mod) % mod;
	}
	return ret;
}

int main () {
	P[0] = 1;
	for (int i = 1; i < maxn; i++) P[i] = P[i-1] * 2 % mod;

	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}
