#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;
#define lson(x) (x<<1)
#define rson(x) ((x<<1)|1)
const int maxn = 2 * 1e5 + 5;
const int inf = 0x3f3f3f3f;

int idx;
struct Node {
	int key, val, cnt, siz, ch[2];
}nd[maxn * 20];

int root[maxn << 2];

void init () {
	idx = 0;
	//nd[idx].key = 0;
	nd[idx].val = -inf;
	nd[idx].cnt = nd[idx].siz = 0;
	//nd[idx].ch[0] = nd[idx].ch[1] = 0;
}

int newNode (int key) {
	idx++;
	nd[idx].key = key;
	nd[idx].val = rand();
	nd[idx].cnt = nd[idx].siz = 1;
	nd[idx].ch[0] = nd[idx].ch[1] = 0;
	return idx;
}

void maintain(int u) {
	nd[u].siz = nd[nd[u].ch[0]].siz + nd[nd[u].ch[1]].siz + nd[u].cnt;
}

void rotate (int& u, int d) {
	int k = nd[u].ch[d];  
	nd[u].ch[d] = nd[k].ch[d^1];
	nd[k].ch[d^1] = u;
	maintain(u);
	maintain(k);  
	u = k;
}

void insert (int& u, int key) {
	if (u == 0) u = newNode(key);
	else if (nd[u].key == key) nd[u].cnt++;
	else {
		int d = nd[u].key < key;
		insert(nd[u].ch[d], key);
		if (nd[u].val < nd[nd[u].ch[d]].val) rotate(u, d);
	}
	maintain(u);
}

void erase (int& u, int key) {
	if (nd[u].key == key) {
		if (nd[u].cnt == 1) {
			if (nd[u].ch[0] == 0 && nd[u].ch[1] == 0) {
				u = 0; return;
			}
			rotate(u, nd[nd[u].ch[0]].val < nd[nd[u].ch[1]].val);
			erase(u, key);
		} else
			nd[u].cnt--;
	} else
		erase(nd[u].ch[nd[u].key < key], key);
	maintain(u);
}

int count (int u, int p) {
	if (u == 0) return 0;
	if (nd[u].key > p) return count(nd[u].ch[0], p);

	return nd[u].cnt + nd[nd[u].ch[0]].siz + count(nd[u].ch[1], p);
}

void modify (int u, int l, int r, int p, int x, int v) {
	//if (v < 0)
	//	printf("%d %d\n", l, r);
	if (v > 0) insert(root[u], x);
	else erase(root[u], x);

	if (l == r) return;
	int mid = (l + r) >> 1;
	if (p <= mid) modify(lson(u), l, mid, p, x, v);
	else modify(rson(u), mid + 1, r, p, x, v);
}

int query (int u, int l, int r, int x, int y, int k) {
	//printf("%d %d\n", l, r);
	if (l == r) return l;

	int mid = (l + r) >> 1;
	int siz = count(root[lson(u)], y) - count(root[lson(u)], x);
	if (siz >= k) return query(lson(u), l, mid, x, y, k);
	else return query(rson(u), mid + 1, r, x, y, k - siz);
}

int N, M, Q, A[maxn], B[maxn], order[maxn], L[maxn], R[maxn], K[maxn];

int find (int x) {
	return lower_bound(B, B + M, x) - B + 1;
}

int main () {
	while (scanf("%d", &N) == 1) {
		memset(root, 0, sizeof(root));
		for (int i = 0; i < N; i++) scanf("%d", &A[i]);
		for (int i = 0; i < N; i++) B[i] = A[i];

		M = N;
		scanf("%d", &Q);
		for (int i = 0; i < Q; i++) {
			scanf("%d%d%d", &order[i], &L[i], &R[i]);
			if (order[i] == 1)
				B[M++] = R[i];
			else
				scanf("%d", &K[i]);
		}

		init();
		sort(B, B + M);
		M = unique(B, B + M) - B;
		for (int i = 0; i < N; i++) {
			modify(1, 1, M, find(A[i]), i + 1, 1);
		}

		for (int i = 0; i < Q; i++) {
			if (order[i] == 1) {
				modify(1, 1, M, find(A[L[i]-1]), L[i], -1);
				A[L[i]-1] = R[i];
				modify(1, 1, M, find(A[L[i]-1]), L[i], 1);
			} else {
				int id = query(1, 1, M, L[i]-1, R[i], K[i]);
				printf("%d\n", B[id-1]);
			}
		}
	}
	return 0;
}
