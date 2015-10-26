#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 100005;
typedef pair<int,int> pii;
#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)

struct SegTree {
	int lc[maxn<<2], rc[maxn<<2], s[maxn<<2];

	void pushup(int u) { s[u] = s[lson(u)] + s[rson(u)]; }

	void build (int u, int l, int r) {
		lc[u] = l, rc[u] = r, s[u] = 1;

		if (l == r) return;

		int mid = (l + r) >> 1;
		build(lson(u), l, mid);
		build(rson(u), mid+1, r);
		pushup(u);
	}

	void modify(int u, int x) {
		if (lc[u] == rc[u]) {
			s[u] = 0;
			return;
		}

		int mid = (lc[u] + rc[u])>>1;
		if (x <= mid) modify(lson(u), x);
		else modify(rson(u), x);
		pushup(u);
	}

	int query(int u, int x) {
		if (lc[u] == rc[u])
			return lc[u];

		int mid = (lc[u] + rc[u])>>1;
		if (s[lson(u)] >= x) return query(lson(u), x);
		else return query(rson(u), x - s[lson(u)]);
	}
}T;

int N, A[maxn];
vector<pii> G;

void init () {
	int h, k;
	scanf("%d", &N);

	G.clear();
	for (int i = 1; i <= N; i++) {
		scanf("%d%d", &h, &k);
		G.push_back(make_pair(h, k));
	}
	sort(G.begin(), G.end());

	T.build(1, 1, N);
}

bool solve () {

	for (int i = 0; i < N; i++) {
		if (G[i].second >= N-i) return false;
		int pre = G[i].second + 1, suf = N-i-G[i].second;
		int pos = min(T.query(1, pre), T.query(1, suf));
		A[pos] = G[i].first;
		T.modify(1, pos);
	}

	for (int i = 1; i <= N; i++)
		printf(" %d", A[i]);
	printf("\n");
	return true;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();
		printf("Case #%d:", kcas);
		if (!solve()) printf(" impossible\n");
	}
	return 0;
}
