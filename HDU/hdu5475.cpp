#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 5;
#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)

int N, mod, P[maxn];
int lc[maxn<<2], rc[maxn<<2], s[maxn<<2];

void pushup(int u) {
	s[u] = 1LL * s[lson(u)] * s[rson(u)] % mod;
}

void build (int u, int l, int r) {
	lc[u] = l, rc[u] = r, s[u] = 1;

	if (l == r) return;
	int mid = (l + r) >> 1;
	build (lson(u), l, mid);
	build (rson(u), mid+1, r);
	pushup(u);
}

void modify(int u, int x, int v) {
	if (lc[u] == x && rc[u] == x) {
		s[u] = v % mod;
		return;
	}

	int mid = (lc[u] + rc[u]) >> 1;
	if (x <= mid) modify(lson(u), x, v);
	else modify(rson(u), x, v);
	pushup(u);
}

int main () {
	int cas, t;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%d%d", &N, &mod);
		build(1, 1, N);
		printf("Case #%d:\n", kcas);
		for (int i = 1; i <= N; i++) {
			scanf("%d%d", &t, &P[i]);
			if (t == 1) modify(1, i, P[i]);
			else modify(1, P[i],  1);
			printf("%d\n", s[1]);
		}
	}
	return 0;
}
