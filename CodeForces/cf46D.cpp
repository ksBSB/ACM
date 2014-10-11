#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 100505;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int lc[maxn << 2], rc[maxn << 2], set[maxn << 2];
int L[maxn << 2], R[maxn << 2], S[maxn << 2]; 

inline int length(int u) {
	return rc[u] - lc[u] + 1;
}

inline void maintain (int u, int v) {
	S[u] = L[u] = R[u] = (v ? length(u) : 0);
}

inline void pushup (int u) {
	S[u] = max(max(S[lson(u)], S[rson(u)]), R[lson(u)] + L[rson(u)]);
	L[u] = L[lson(u)] + (L[lson(u)] == length(lson(u)) ? L[rson(u)] : 0);
	R[u] = R[rson(u)] + (R[rson(u)] == length(rson(u)) ? R[lson(u)] : 0);
}

inline void pushdown(int u) {
	if (set[u] != -1) {
		maintain(lson(u), set[u]);
		maintain(rson(u), set[u]);
		set[u] = -1;
	}
}

void build (int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;
	set[u] = -1;

	if (l == r) {
		maintain(u, 1);
		return;
	}

	int mid = (l + r) / 2;
	build(lson(u), l, mid);
	build(rson(u), mid + 1, r);
	pushup(u);
}

void modify (int u, int l, int r, int v) {
	if (l <= lc[u] && rc[u] <= r) {
		maintain(u, v);
		return;
	}

	pushdown(u);
	int mid = (lc[u] + rc[u]) / 2;
	if (l <= mid)
		modify(lson(u), l, r, v);
	if (r > mid)
		modify(rson(u), l, r, v);
	pushup(u);
}

int query(int u, int k) {
	if (S[u] < k)
		return -1;

	if (lc[u] == rc[u])
		return lc[u];

	pushdown(u);
	int mid = (lc[u] + rc[u]) / 2, ret;
	if (S[lson(u)] >= k)
		ret = query(lson(u), k);
	else if (R[lson(u)] + L[rson(u)] >= k)
		ret = mid - R[lson(u)] + 1;
	else
		ret = query(rson(u), k);
	pushup(u);
	return ret;
}

int N, M, B, F;
int op[105][2];

int main () {
	scanf("%d%d%d%d", &N, &B, &F, &M);
	build(1, 0, B + F + N - 1);

	int x, y;
	for (int i = 1; i <= M; i++) {
		scanf("%d%d", &x, &y);
		if (x == 1) {
			op[i][0] = query(1, y + B + F);
			if (op[i][0] != -1) {
				//op[i][0] = 
				op[i][1] = op[i][0] + y - 1;
				modify(1, op[i][0] + B, op[i][1] + B, 0);
			}
			printf("%d\n", op[i][0]);
		} else
			modify(1, op[y][0] + B, op[y][1] + B, 1);
	}
	return 0;
}
