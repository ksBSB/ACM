#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
#define lowbit(x) ((x)&(-x))
const int maxn = 100005;
typedef pair<int,int> pii;

int N, fenw[maxn];

void add(int x, int v) {
	while (x <= N) {
		fenw[x] += v;
		x += lowbit(x);
	}
}

int sum(int x) {
	int ret = 0;
	while (x) {
		ret += fenw[x];
		x -= lowbit(x);
	}
	return ret;
}

int M, A[maxn], P[maxn], ans[maxn];
vector<pii> G[maxn];

void init () {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &A[i]);
		G[i].clear();
	}

	memset(P, -1, sizeof(P));
	memset(fenw, 0, sizeof(fenw));

	int l, r;
	for (int i = 1; i <= M; i++) {
		scanf("%d%d", &l, &r);
		G[l].push_back(make_pair(r, i));
	}
}

void solve () {
	for (int i = N; i; i--) {
		add(i, 1);
		P[A[i]] = i;
		int pre = P[A[i]-1], suf = P[A[i]+1];
		if (pre != -1) add(pre, -1);
		if (suf != -1) add(suf, -1);

		for (int j = 0; j < G[i].size(); j++) {
			int r = G[i][j].first;
			int k = G[i][j].second;
			ans[k] = sum(r) - sum(i-1);
		}
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		solve();
		for (int i = 1; i <= M; i++)
			printf("%d\n", ans[i]);
	}
	return 0;
}
