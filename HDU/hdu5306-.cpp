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

int L[maxn << 2], R[maxn << 2], M[maxn << 2], T[maxn << 2], C[maxn << 2];
ll S[maxn << 2];

inline void pushup(int u) {
	M[u] = max(M[lson(u)], M[rson(u)]);
	S[u] = S[lson(u)] + S[rson(u)];
	C[u] = C[lson(u)] + C[rson(u)];
}

inline void maintain (int u, int alter) {
	if (T[u] != 0 && T[u] <= alter)
		return;
	T[u] = alter;
	if (C[u] != R[u] - L[u] + 1) {
		M[u] = alter;
		S[u] += 1LL * (R[u] - L[u] + 1 - C[u]) * alter;
		C[u] = R[u] - L[u] + 1;
	}
}

void dfs (int u, int alter) {
	if (M[u] <= alter)
		return;

	T[u] = 0;
	if (L[u] == R[u]) {
		S[u] = M[u] = C[u] = 0;
		return;
	}
	dfs(lson(u), alter);
	dfs(rson(u), alter);
	pushup(u);
}

inline void pushdown(int u) {
	if (T[u] == 0)
		return ;
	maintain(lson(u), T[u]);
	maintain(rson(u), T[u]);
}

void build (int u, int l, int r) {
	L[u] = l, R[u] = r, T[u] = 0;

	if (l == r) {
		read(M[u]);
		//scanf("%d", &M[u]);
		T[u] = S[u] = M[u];
		C[u] = 1;
		return;
	}

	int mid = (l + r) >> 1;
	build (lson(u), l, mid);
	build (rson(u), mid + 1, r);
	pushup(u);
}

void modify (int u, int l, int r, int alter) {

	if (M[u] <= alter)
		return;

	if (l <= L[u] && R[u] <= r) {
		dfs(u, alter);
		maintain(u, alter);
		return;
	}

	int mid = (L[u] + R[u]) >> 1;
	pushdown(u);
	if (l <= mid)
		modify(lson(u), l, r, alter);
	if (r > mid)
		modify(rson(u), l, r, alter);
	pushup(u);
}

void query (int u, int l, int r, ll& sum, int& mx) {
	if (l <= L[u] && R[u] <= r) {
		sum = sum + S[u];
		mx = max(mx, M[u]);
		return;
	}

	int mid = (L[u] + R[u]) >> 1;
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
