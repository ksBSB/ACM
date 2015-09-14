#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1000000 + 5;
typedef long long ll;
#define lson(x) (x<<1)
#define rson(x) ((x<<1)|1)

/*********** input *************/
char *ch, *ch1, buf[40*1024000+5], buf1[40*1024000+5];    
void read(int &x)   {    
	for (++ch; *ch <= 32; ++ch);    
	for (x = 0; '0' <= *ch; ch++)    x = x * 10 + *ch - '0';    
}
/******************************/

struct Node {
	int L, R, M, T, C;
	ll S;
}nd[maxn << 2];;

inline void pushup(int u) {
	nd[u].M = max(nd[lson(u)].M, nd[rson(u)].M);
	nd[u].S = nd[lson(u)].S + nd[rson(u)].S;
	nd[u].C = nd[lson(u)].C + nd[rson(u)].C;
}

inline void maintain (int u, int alter) {
	if (nd[u].T != 0 && nd[u].T <= alter)
		return;
	nd[u].T = alter;
	if (nd[u].C != nd[u].R - nd[u].L + 1) {
		nd[u].M = alter;
		nd[u].S += 1LL * (nd[u].R - nd[u].L + 1 - nd[u].C) * alter;
		nd[u].C = nd[u].R - nd[u].L + 1;
	}
}

void dfs (int u, int alter) {
	if (nd[u].M <= alter)
		return;

	nd[u].T = 0;
	if (nd[u].L == nd[u].R) {
		nd[u].S = nd[u].M = nd[u].C = 0;
		return;
	}
	dfs(lson(u), alter);
	dfs(rson(u), alter);
	pushup(u);
}

inline void pushdown(int u) {
	if (nd[u].T == 0)
		return ;
	maintain(lson(u), nd[u].T);
	maintain(rson(u), nd[u].T);
}

void build (int u, int l, int r) {
	nd[u].L = l, nd[u].R = r, nd[u].T = 0;

	if (l == r) {
		read(nd[u].M);
		//scanf("%d", &nd[u].M);
		nd[u].T = nd[u].S = nd[u].M;
		nd[u].C = 1;
		return;
	}

	int mid = (l + r) >> 1;
	build (lson(u), l, mid);
	build (rson(u), mid + 1, r);
	pushup(u);
}

void modify (int u, int l, int r, int alter) {

	if (nd[u].M <= alter)
		return;

	if (l <= nd[u].L && nd[u].R <= r) {
		dfs(u, alter);
		maintain(u, alter);
		return;
	}

	int mid = (nd[u].L + nd[u].R) >> 1;
	pushdown(u);
	if (l <= mid)
		modify(lson(u), l, r, alter);
	if (r > mid)
		modify(rson(u), l, r, alter);
	pushup(u);
}

void query (int u, int l, int r, ll& sum, int& mx) {
	if (l <= nd[u].L && nd[u].R <= r) {
		sum = sum + nd[u].S;
		mx = max(mx, nd[u].M);
		return;
	}

	int mid = (nd[u].L + nd[u].R) >> 1;
	pushdown(u);
	if (l <= mid)
		query(lson(u), l, r, sum, mx);
	if (r > mid)
		query(rson(u), l, r, sum, mx);
	pushup(u);
}

int main () {

	ch = buf - 1;    
	ch1 = buf1 - 1;    
	fread(buf, 1, 1000 * 35 * 1024, stdin);  

	int cas, n, m, k, x, y, t, mx;
	ll s;
	read(cas);
	//scanf("%d", &cas);
	while (cas--) {
		read(n), read(m);
		//scanf("%d%d", &n, &m);
		build(1, 1, n);
		for (int i = 0; i < m; i++) {
			read(k), read(x), read(y);
			//scanf("%d%d%d", &k, &x, &y);
			if (k) {
				s = mx = 0;
				query(1, x, y, s, mx);
				if (k == 1)
					printf("%d\n", mx);
				else
					printf("%lld\n", s);
			} else {
				read(t);
				//scanf("%d", &t);
				modify(1, x, y, t);
			}
		}
	}
	return 0;
}
