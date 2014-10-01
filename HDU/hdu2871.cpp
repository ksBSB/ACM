#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 50005;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int lc[maxn << 2], rc[maxn << 2], set[maxn << 2];
int L[maxn << 2], R[maxn << 2], S[maxn << 2];

inline int length (int u) {
	return rc[u] - lc[u] + 1;
}

inline void maintain (int u, int v) {
	set[u] = v;
	L[u] = R[u] = S[u] = (v ? 0 : length(u));
}

inline void pushup (int u) {
	S[u] = max( max(S[lson(u)], S[rson(u)]), L[rson(u)] + R[lson(u)]);
	L[u] = L[lson(u)] + (L[lson(u)] == length(lson(u)) ? L[rson(u)] : 0);
	R[u] = R[rson(u)] + (R[rson(u)] == length(rson(u)) ? R[lson(u)] : 0);
}

inline void pushdown (int u) {
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
		maintain(u, 0);
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

int query (int u, int len) {
	if (S[u] < len)
		return 0;

	if (lc[u] == rc[u])
		return lc[u];

	pushdown(u);
	int mid = (lc[u] + rc[u]) / 2, ret;
	if (S[lson(u)] >= len)
		ret = query(lson(u), len);
	else if (L[rson(u)] + R[lson(u)] >= len)
		ret = mid - R[lson(u)] + 1;
	else
		ret = query(rson(u), len);
	pushup(u);
	return ret;
}

typedef pair<int, int> pii;
int N, M;
vector<pii> list;

int find (int k) {
	int l = 0, r = list.size() - 1;
	while (l <= r) {
		int mid = (l + r) / 2;
		if (list[mid].first > k)
			r = mid - 1;
		else
			l = mid + 1;
	}
	return l;
}

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		build (1, 1, N);
		list.clear();

		int k;
		char op[5];
		while (M--) {
			scanf("%s", op);
			if (op[0] == 'R') {
				modify(1, 1, N, 0);
				list.clear();
				printf("Reset Now\n");
			} else {
				scanf("%d", &k);
				if (op[0] == 'N') {
					int x = query(1, k);

					if (x) {
						modify(1, x, x + k - 1, 1);
						pii u = make_pair(x, x + k - 1);
						list.insert(list.begin() + find(x), u);
						printf("New at %d\n", x);
					} else
						printf("Reject New\n");

				} else if (op[0] == 'F') {
					int x = find(k) - 1;

					if (x != -1 && k <= list[x].second) {
						modify(1, list[x].first, list[x].second, 0);
						printf("Free from %d to %d\n", list[x].first, list[x].second);
						list.erase(list.begin() + x);
					} else
						printf("Reject Free\n");

				} else if (op[0] == 'G') {
					if (k <= list.size()) {
						printf("Get at %d\n", list[k-1].first);
					} else
						printf("Reject Get\n");
				}
			}
		}
		printf("\n");
	}
	return 0;
}
