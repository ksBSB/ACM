#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1005;
const int maxm = 105;
const int maxs = 1e5 + 1;
#define lowbit(x) ((x)&(-x))

int N, M, cn[maxn], fenw[maxs + 5];
ll K, clas[maxn][maxm];
ll idx[maxs + 5], tmp[maxs + 5];

inline void add(int x, int d) {
	while (x <= maxs) {
		fenw[x] += d;
		x += lowbit(x);
	}
}

inline int sum(int x) {
	int ret = 0;
	while (x) {
		ret += fenw[x];
		x -= lowbit(x);
	}
	return ret;
}

void init () {
	int n = M = 0;
	scanf("%d%I64d", &N, &K);
	memset(cn, 0, sizeof(cn));
	memset(fenw, 0, sizeof(fenw));

	for (int i = 1; i <= N; i++) {
		scanf("%d", &cn[i]);
		for (int j = 0; j < cn[i]; j++) {
			scanf("%I64d", &clas[i][j]);
			tmp[n++] = clas[i][j];
		}
	}

	sort(tmp, tmp + n);
	idx[M++] = tmp[0];
	for (int i = 1; i < n; i++) {
		if (tmp[i] != tmp[i-1])
			idx[M++] = tmp[i];
	}
}

inline int find (ll x) {
	return (lower_bound(idx, idx + M, x) - idx) + 1;
}

void insert(int d) {
	for (int i = 0; i < cn[d]; i++) {
		int pos = find(clas[d][i]);
		add(pos, 1);
	}
}

ll query(int d) {
	ll ret = 0;
	for (int i = 0; i < cn[d]; i++) {
		int pos = find(K - clas[d][i] + 1);
		ret += sum(maxs) - sum(pos-1);
	}
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();

		ll ans = 0;
		insert(1);
		for (int i = 2; i <= N; i++) {
			ans += query(i);
			insert(i);
		}
		printf("%I64d\n", ans);
	}
	return 0;
}
