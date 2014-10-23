#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 1e5 + 5;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int lc[maxn << 2], rc[maxn << 2], L[maxn << 2], R[maxn << 2], S[maxn << 2];

void pushup(int u) {
	S[u] = max(max(S[lson(u)], S[rson(u)]), R[lson(u)] + L[rson(u)]);
	L[u] = L[lson(u)] + (L[lson(u)] == rc[lson(u)] - lc[lson(u)] + 1 ? L[rson(u)] : 0);
	R[u] = R[rson(u)] + (R[rson(u)] == rc[rson(u)] - lc[rson(u)] + 1 ? R[lson(u)] : 0); 
}

void build (int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;
	L[u] = R[u] = S[u] = 0;

	if (l == r)
		return;

	int mid = (l + r) >> 1;
	build(lson(u), l,  mid);
	build(rson(u), mid + 1, r);
	pushup(u);
}

void modify(int u, int x, int w) {
	if (lc[u] == x && x == rc[u]) {
		S[u] = R[u] = L[u] = w ? rc[u] - lc[u] + 1 : 0;
		return;
	}

	int mid = (lc[u] + rc[u]) >> 1;
	if (x <= mid)
		modify(lson(u), x, w);
	else
		modify(rson(u), x, w);
	pushup(u);
}

typedef pair<int, int> pii;
vector<pii> vec;

int main () {
	int cas;
	scanf("%d", &cas);

	while (cas--) {
		int n, x;
		vec.clear();

		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &x);
			vec.push_back(make_pair(x, i));
		}

		sort(vec.begin(), vec.end());

		build(1, 1, n);
		int mv = 0;
		for (int k = 1; k <= n; k++) {
			while (S[1] < k)
				modify(1, vec[mv++].second, 1);
			printf("%d\n", vec[mv-1].first);
		}
	}
	return 0;
}
