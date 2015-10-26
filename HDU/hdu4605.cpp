#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 5;

/***********************************/

int P;
struct Node {
	int key, val;
	int cnt, siz;
	int uri, sri, ch[2];
}nd[maxn * 20];

int newNode (int key, int rit) {
	P++;
	nd[P].key = key;
	nd[P].val = rand();
	nd[P].cnt = nd[P].siz = 1;
	nd[P].uri = nd[P].sri = rit;
	nd[P].ch[0] = nd[P].ch[1] = 0;
	return P;
}

void maintain(int u) {
	int ls = nd[u].ch[0], rs = nd[u].ch[1];
	nd[u].siz = nd[ls].siz + nd[rs].siz + nd[u].cnt;
	nd[u].sri = nd[ls].sri + nd[rs].sri + nd[u].uri;
}

void rotate(int& u, int d) {
	int k = nd[u].ch[d];    
	nd[u].ch[d] = nd[k].ch[d^1];  
	nd[k].ch[d^1] = u;  
	maintain(u);  
	maintain(k);    
	u = k; 
}

int insert(int v, int key, int rit) {

	if (v == 0) return newNode(key, rit);

	int u = ++P;
	nd[u] = nd[v];

	if (nd[u].key == key) {
		nd[u].cnt++;
		if (rit) nd[u].uri++;
	} else {
		int d = nd[u].key < key;
		nd[u].ch[d] = insert(nd[u].ch[d], key, rit);
		if (nd[u].val < nd[nd[u].ch[d]].val) rotate(u, d);
	}
	maintain(u);
	return u;
}

bool query(int u, int key, int& x, int& y) {
	if (u == 0) return true;

	if (nd[u].key == key) return false;

	if (nd[u].key > key)
		return query(nd[u].ch[0], key, x, y);

	int ls = nd[u].ch[0];
	x += nd[ls].sri + nd[u].uri;
	y += nd[ls].siz + nd[u].cnt;

	return query(nd[u].ch[1], key, x, y);
}

/***********************************/


int N, M, Q, F[maxn], W[maxn], L[maxn], R[maxn];
int T[maxn];

void dfs (int u, int rit) {
	if (u == 0) return;

	if (u != 1)
		T[u] = insert(T[F[u]], W[F[u]], rit);
	dfs(L[u], 0);
	dfs(R[u], 1);
}

void init () {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &W[i]);
	memset(L, 0, sizeof(L));
	memset(R, 0, sizeof(R));

	scanf("%d", &M);
	int u, a, b;
	while (M--) {
		scanf("%d%d%d", &u, &a, &b);
		F[a] = F[b] = u;
		L[u] = a; R[u] = b;
	}

	P = T[0] = 0;
	nd[P].cnt = nd[P].siz = 0;
	nd[P].uri = nd[P].sri = 0;
	nd[P].ch[0] = nd[P].ch[1] = 0;

	dfs(1, 0);
}

void solve (int u, int w) {
	int x = 0, y = 0;
	if (!query(T[u], w, x, y))
		printf("0\n");
	else
		printf("%d %d\n", x, y * 2 + nd[T[u]].siz);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();

		scanf("%d", &Q);
		int v, x;
		while (Q--) {
			scanf("%d%d", &v, &x);
			solve(v, x);
		}
	}
	return 0;
}
