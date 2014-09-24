#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 1000005;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)+1)

struct Node {
	int l, r, s, v;
	void set (int l, int r, int s, int v) {
		this->l = l;
		this->r = r;
		this->s = s;
		this->v = v;
	}

	void set (int x) {
		this->v = x;
		this->s = x;
	}
}nd[maxn * 4];

int N, M;
vector<int> ans;

void pushup (int u) {
	nd[u].s = nd[lson(u)].s | nd[rson(u)].s;
}

void pushdown(int u) {
	if (nd[u].v) {
		nd[lson(u)].set(nd[u].v);
		nd[rson(u)].set(nd[u].v);
		nd[u].v = 0;
	}
}

void build (int u, int l, int r) {
	nd[u].set(l, r, 0, 0);

	if (l == r) {
		nd[u].s = 2;
		return ;
	}

	int mid = (l + r) / 2;
	build (lson(u), l, mid);
	build (rson(u), mid + 1, r);
	pushup(u);
}

void modify (int u, int l, int r, int x) {
	if (l <= nd[u].l && nd[u].r <= r) {
		nd[u].set(x);
		return;;
	}

	pushdown(u);
	int mid = (nd[u].l + nd[u].r) / 2;
	if (l <= mid)
		modify(lson(u), l, r, x);
	if (r > mid)
		modify(rson(u), l, r, x);
	pushup(u);
}

int query(int u, int l, int r) {
	if (l <= nd[u].l && nd[u].r <= r)
		return nd[u].s;

	pushdown(u);
	int mid = (nd[u].l + nd[u].r) / 2, ret = 0;
	if (l <= mid)
		ret |= query(lson(u), l, r);
	if (r > mid)
		ret |= query(rson(u), l, r);
	pushup(u);
	return ret;
}

int main () {
	while (scanf("%d%d", &N, &M) == 2 && N + M) {
		build (1, 1, N);

		int l, r, x;
		char order[10];
		for (int i = 0; i < M; i++) {
			scanf("%s%d%d", order, &l, &r);
			if (order[0] == 'P') {
				scanf("%d", &x);
				modify(1, l, r, 1<<(x-1));
			} else {
				ans.clear();
				int s = query(1, l, r);
				for (int i = 0; i < 30; i++)
					if (s & (1<<i))
						ans.push_back(i+1);

				printf("%d", ans[0]);
				for (int i = 1; i < ans.size(); i++)
					printf(" %d", ans[i]);
				printf("\n");
			}
		}
	}
	return 0;
}
