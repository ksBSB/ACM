#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)+1)
const int maxn = 1e5+5;

struct Node {
	int l, r, val;
	Node (int l = 0, int r = 0, int val = 0) {
		this->set(l, r, val);
	}
	void set (int l, int r, int val) {
		this->l = l;
		this->r = r;
		this->val = val;
	}
}node[maxn*4];

int N, M, arr[maxn];

void pushup (int u) {
	int val = min(node[lson(u)].val, node[rson(u)].val);
	node[u].set(node[lson(u)].l, node[rson(u)].r, val);
}

void build_segTree (int u, int l, int r) {

	if (l == r) {
		node[u].set(l, r, arr[l]);
		return;
	}

	int mid = (l + r) / 2;
	build_segTree(lson(u), l, mid);
	build_segTree(rson(u), mid + 1, r);
	pushup(u);
}

void insert_segTree (int u, int pos, int v) {
	if (node[u].l == pos && node[u].r == pos) {
		node[u].val = v;
		return;
	}

	int mid = (node[u].l + node[u].r) / 2;

	if (pos <= mid)
		insert_segTree(lson(u), pos, v);
	else
		insert_segTree(rson(u), pos, v);
	pushup(u);
}

int query_segTree (int u, int l, int r) {
	if (l <= node[u].l && node[u].r <= r)
		return node[u].val;

	int mid = (node[u].l + node[u].r) / 2;

	if (r <= mid)
		return query_segTree(lson(u), l, r);
	else if (l > mid)
		return query_segTree(rson(u), l, r);
	else
		return min(query_segTree(lson(u), l, r), query_segTree(rson(u), l, r));
}

void get_number (int& n, int* num, char* s) {
	n = 0;
	int len = strlen(s), u = 0;

	for (int i = 0; i < len; i++) {
		if (s[i] >= '0' && s[i] <= '9')
			u = u * 10 + s[i] - '0';
		else if (s[i] == ',' || s[i] == ')') {
			num[n++] = u;
			u = 0;
		} else
			u = 0;
	}
}

void solve () {
	int n, num[50];
	char order[50];

	scanf("%s", order);
	get_number(n, num, order);

	if (order[0] == 's') {
		int tmp = arr[num[0]];
		for (int i = 0; i < n - 1; i++) {
			insert_segTree(1, num[i], arr[num[i+1]]);
			arr[num[i]] = arr[num[i+1]];
		}
		insert_segTree(1, num[n-1], tmp);
		arr[num[n-1]] = tmp;
	} else if (order[0] == 'q')
		printf("%d\n", query_segTree(1, num[0], num[1]));
}

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		for (int i = 1; i <= N; i++)
			scanf("%d", &arr[i]);
		build_segTree(1, 1, N);

		for (int i = 0; i < M; i++)
			solve();
	}
	return 0;
}
