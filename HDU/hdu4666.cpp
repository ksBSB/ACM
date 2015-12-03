#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
const int maxn = 60005;
const int inf = 0x3f3f3f3f;

int lc[maxn<<2], rc[maxn<<2], mi[maxn<<2], mx[maxn<<2];

void pushup(int u) {
	mi[u] = min(mi[lson(u)], mi[rson(u)]);
	mx[u] = max(mx[lson(u)], mx[rson(u)]);
}

void build (int u, int l, int r) {
	lc[u] = l, rc[u] = r;
	mi[u] = inf, mx[u] = -inf;

	if (l == r) return;

	int mid = (l + r) >> 1;
	build(lson(u), l, mid);
	build(rson(u), mid+1, r);
	pushup(u);
}

void modify(int u, int x, int v) {
	if (lc[u] == rc[u]) {
		mi[u] = mx[u] = v;
		return ;
	}

	int mid = (lc[u] + rc[u]) >> 1;
	if (x <= mid) modify(lson(u), x, v);
	else modify(rson(u), x, v);
	pushup(u);
}

void clear(int u, int x) {
	if (lc[u] == rc[u]) {
		mi[u] = inf;
		mx[u] = -inf;
		return ;
	}

	int mid = (lc[u] + rc[u]) >> 1;
	if (x <= mid) clear(lson(u), x);
	else clear(rson(u), x);
	pushup(u);
}

int N, K, ans[maxn];
int op[maxn], id[maxn], P[maxn][5];

void init () {
	for (int i = 1; i <= N; i++) {
		scanf("%d", &op[i]);
		if (op[i]) scanf("%d", &id[i]);
		else {
			for (int j = 0; j < K; j++)
				scanf("%d", &P[i][j]);
		}
	}
	memset(ans, 0, sizeof(ans));
}

int get(int* x, int s) {
	int ret = 0;
	for (int i = 0; i < K; i++) {
		if (s&(1<<i)) ret += x[i];
		else ret -= x[i];
	}
	return ret;
}

int main () {
	while (scanf("%d%d", &N, &K) == 2) {
		init();
		for (int i = 0; i < (1<<K); i++) {
			build(1, 1, N);
			for (int j = 1; j <= N; j++) {
				if (op[j]) clear(1, id[j]);
				else {
					int tmp = get(P[j], i);
					modify(1, j, tmp);
				}
				ans[j] = max(ans[j], mx[1] - mi[1]);
			}
		}
		for (int i = 1; i <= N; i++)
			printf("%d\n", ans[i]);
	}
	return 0;
}
