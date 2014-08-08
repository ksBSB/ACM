#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
const int maxn = 105;

vector<int> g[maxn];
int N, M, s[maxn], val[maxn];

inline int bitcount (int x) {
	return x == 0 ? x : bitcount(x>>1) + (x&1);
}

int SG (int x) {

	if (s[x] != -1)
		return s[x];

	map<int, int> vis;

	int n = g[x].size();
	if (n == 0)
		return s[x] == 0;

	for (int i = 0; i < (1<<n); i++) {
		int bit = bitcount(i);

		if (bit > val[x] || (bit&1) != (val[x]&1))
			continue;

		int tmp = 0;
		for (int j = 0; j < n; j++) {
			if (i&(1<<j))
				tmp ^= SG(g[x][j]);
		}
		vis[tmp] = 1;
	}

	int ret = -1;
	while (vis.count(++ret));
	return s[x] = ret;
}

void init () {
	scanf("%d%d", &N, &M);
	for (int i = 0; i < maxn; i++)
		g[i].clear();

	int u, v;
	for (int i = 0; i < M; i++) {
		scanf("%d%d", &u, &v);
		g[u].push_back(v);
	}

	for (int i = 0; i < N; i++)
		scanf("%d", &val[i]);

	memset(s, -1, sizeof(s));
	for (int i = 0; i < N; i++)
		s[i] = SG(i);
}

void solve () {
	int Q;
	scanf("%d", &Q);

	for (int i = 1; i <= Q; i++) {
		int ret = 0, x;
		for (int j = 0; j < N; j++) {
			scanf("%d", &x);
			if (x&1)
				ret ^= s[j];
		}
		printf("Round#%d: %s\n", i, ret ? "WINNING" : "LOSING");
	}
	printf("\n");
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int k = 1; k <= cas; k++) {
		init();

		printf("Game#%d:\n", k);
		solve();
	}
	return 0;
}
