#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 20005;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)+1)

struct Node {
	int l, r, v, s;
	void set(int l, int r, int v, int s) {
		this->l = l;
		this->r = r;
		this->v = v;
		this->s = s;
	}
	void maintain() {
		v = 1;
		s = r - l + 1;
	}
}nd[maxn * 4];

int N, L[maxn], R[maxn];
vector<int> vec, g;

void pushup(int u) {
	nd[u].s = nd[lson(u)].s + nd[rson(u)].s;
	nd[u].v = (nd[lson(u)].v == nd[rson(u)].v && nd[lson(u)].v == 1 ? 1 : 0);
}

void pushdown(int u) {
	if (nd[u].v) {
		nd[lson(u)].v = nd[rson(u)].v = 1;
		nd[lson(u)].maintain();
		nd[rson(u)].maintain();
		nd[u].v = 0;
	}
}

void build (int u, int l, int r) {
	nd[u].set(l, r, 0, 0);

	if (l == r)
		return;

	int mid = (l + r) / 2;
	build(lson(u), l, mid);
	build(rson(u), mid + 1, r);
	pushup(u);
}

void init () {
	scanf("%d", &N);

	vec.clear();
	for (int i = 0; i < N; i++) {
		scanf("%d%d", &L[i], &R[i]);
		vec.push_back(L[i]);
		vec.push_back(R[i] + 1);
	}
	sort(vec.begin(), vec.end());

	g.clear();
	g.push_back(vec[0]);
	for (int i = 1; i < vec.size(); i++) {
		if (vec[i] != vec[i-1])
			g.push_back(vec[i]);
	}

	for (int i = 0; i < N; i++) {
		L[i] = lower_bound(g.begin(), g.end(), L[i]) - g.begin();
		R[i] = lower_bound(g.begin(), g.end(), R[i] + 1) - g.begin();
	}

	build(1, 0, g.size());
}

int modify (int u, int l, int r) {
	if (l <= nd[u].l && nd[u].r <= r) {
		int tmp = nd[u].s;
		nd[u].maintain();
		return nd[u].s - tmp;
	}

	pushdown(u);
	int mid = (nd[u].l + nd[u].r) / 2, ret = 0;
	if (l <= mid)
		ret += modify(lson(u), l, r);
	if (r > mid)
		ret += modify(rson(u), l, r);
	pushup(u);
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();

		int ret = 0;
		for (int i = N - 1; i >= 0; i--) {
			if(modify(1, L[i], R[i]-1))
				ret++;
		}
		printf("%d\n", ret);
	}
	return 0;
}
