#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 50005;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int lc[maxn << 2], rc[maxn << 2];
int L[maxn << 2], R[maxn << 2], S[maxn << 2];

inline int length(int u) {
	return rc[u] - lc[u] + 1;
}

inline void maintain(int u, int v) {
	S[u] = L[u] = R[u] = (v ? length(u) : 0);
}

inline void pushup (int u) {
	S[u] = max (max(S[lson(u)], S[rson(u)]), R[lson(u)] + L[rson(u)]);
	L[u] = L[lson(u)] + (L[lson(u)] == length(lson(u)) ? L[rson(u)] : 0);
	R[u] = R[rson(u)] + (R[rson(u)] == length(rson(u)) ? R[lson(u)] : 0);
}

void build (int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;

	if (l == r) {
		maintain(u, 1);
		return;
	}

	int mid = (l + r) / 2;
	build(lson(u), l, mid);
	build(rson(u), mid + 1, r);
	pushup(u);
}

void modify (int u, int x, int v) {
	if (lc[u] == x && rc[u] == x) {
		maintain(u, v);
		return;
	}

	int mid = (lc[u] + rc[u]) / 2;
	if (x <= mid)
		modify(lson(u), x, v);
	else
		modify(rson(u), x, v);
	pushup(u);
}

int query (int u, int x) {
	if (S[u] == length(u))
		return S[u];

	if (lc[u] == rc[u])
		return 0;

	int mid = (lc[u] + rc[u]) / 2;
	if (x <= mid) {
		if (x >= mid - R[lson(u)] + 1)
			return R[lson(u)] + L[rson(u)];
		else
			return query(lson(u), x);
	} else {
		if (x <= mid + L[rson(u)])
			return R[lson(u)] + L[rson(u)];
		else
			return query(rson(u), x);
	}
}

int N, M;
vector<int> des;

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		des.clear();
		build(1, 1, N);

		int x;
		char op[5];
		while (M--) {
			scanf("%s", op);
			if (op[0] == 'R') {
				x = des[des.size()-1];
				modify(1, x, 1);
				des.pop_back();
			} else {
				scanf("%d", &x);
				if (op[0] == 'D') {
					modify(1, x, 0);
					des.push_back(x);
				} else
					printf("%d\n", query(1, x));
			}
		}
	}
	return 0;
}
