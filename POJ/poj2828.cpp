#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 200005;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)+1)

struct Node {
	int l, r, s;
	void set(int l, int r, int s) {
		this->l = l;
		this->r = r;
		this->s = s;
	}
}nd[maxn * 4];

int N, val[maxn], pos[maxn], rec[maxn];

void build (int u, int l, int r) {
	nd[u].set(l, r, r - l + 1);

	if (l == r)
		return ;
	int mid = (l + r) / 2;
	build(lson(u), l, mid);
	build(rson(u), mid + 1, r);
}

int query (int u, int x) {
	nd[u].s--;

	if (nd[u].l == nd[u].r)
		return nd[u].l;

	if (nd[lson(u)].s >= x)
		return query(lson(u), x);
	else
		return query(rson(u), x - nd[lson(u)].s);
}

int main () {
	while (scanf("%d", &N) == 1) {
		build(1, 0, N - 1);
		for (int i = 0; i < N; i++)
			scanf("%d%d", &pos[i], &val[i]);

		for (int i = N - 1; i >= 0; i--)
			rec[query(1, pos[i] + 1)] = i;

		printf("%d", val[rec[0]]);
		for (int i = 1; i < N; i++)
			printf(" %d", val[rec[i]]);
		printf("\n");
	}
	return 0;
}
