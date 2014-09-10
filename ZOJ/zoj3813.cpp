#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)+1)
typedef long long ll;
const int maxn = 200005;
const ll mod = 1e9+7;

struct Node {
	int l, r;
	ll sum[2], ans[2];
}nd[maxn*4];

int N, M;
char str[maxn];

void pushup(int u);
Node query(int u, int x, int y);
void modify (int u, int x, int v);
void build_segTree(int u, int l, int r);

inline ll cal(ll n) {
	if (n&1)
		return ((n-1) / 2 % mod) * (n % mod) % mod;
	else
		return (n / 2 % mod) * ((n-1) % mod) % mod;
}

void init () {
	scanf("%s", str);
	N = strlen(str);
	M = 2 * N;
	build_segTree(1, 1, M);
}

int solve (ll x, ll y) {
	ll p = (x-1) / M, q = (y-1) / M;

	if (p != q) {
		int d = (x % 2) ^ 1;
		ll n = (q - p - 1) % mod;

		Node pre = query(1, (x-1) % M + 1, M);
		Node mid = query(1, 1, M);
		Node suf = query(1, 1, (y-1) % M + 1);

		// pre;
		ll ret = (pre.ans[0] + pre.sum[0] * (n * M % mod)) % mod;
		ll s = (pre.sum[0] + mid.sum[d] * n) % mod;

		// mid;
		ret = (ret + mid.ans[d] * n) % mod;
		//ret = (ret + (mid.sum[d] * (((n&1) ? ((n-1)/2)%mod*n : (n/2)%mod*(n-1))%mod)) * M)  % mod;
		ret = (ret + (mid.sum[d] * cal(n) % mod) * M)  % mod;

		// suf;
		ret = (ret + s * (suf.r - suf.l + 1) + suf.ans[d]) % mod;
		return ret;
	} else
		return query(1, (x-1) % M + 1, (y-1) % M + 1).ans[0];
}

int main () {
	int cas, n, k;
	ll x, y;

	scanf("%d", &cas);
	while (cas--) {
		init();

		scanf("%d", &n);
		while (n--) {
			scanf("%d%lld%lld", &k, &x, &y);

			if (k == 1) {
				modify(1, x, y);
				modify(1, x + N, y);
			} else
				printf("%d\n", solve(x, y));
		}
	}
	return 0;
}

void pushup (int u) {
	int d = (nd[lson(u)].r - nd[lson(u)].l + 1) & 1;
	int L = (nd[rson(u)].r - nd[rson(u)].l + 1) % mod;

	for (int i = 0; i < 2; i++) {
		nd[u].sum[i] = (nd[lson(u)].sum[i] + nd[rson(u)].sum[i^d]) % mod;
		nd[u].ans[i] = (nd[lson(u)].ans[i] + nd[lson(u)].sum[i] * L % mod + nd[rson(u)].ans[i^d]) % mod;
	}
}

Node query(int u, int l, int r) {
	if (l == nd[u].l && nd[u].r == r)
		return nd[u];

	int mid = (nd[u].l + nd[u].r) / 2;
	if (l > mid)
		return query(rson(u), l, r);
	else if (r <= mid)
		return query(lson(u), l, r);
	else {
		Node ret;
		ret.l = l; ret.r = r;

		Node lc = query(lson(u), l, mid);
		Node rc = query(rson(u), mid + 1, r);

		int d = (lc.r - lc.l + 1) & 1;
		int L = (rc.r - rc.l + 1) % mod;

		for (int i = 0; i < 2; i++) {
			ret.sum[i] = (lc.sum[i] + rc.sum[i^d]) % mod;
			ret.ans[i] = (lc.ans[i] + lc.sum[i] * L % mod + rc.ans[i^d]) % mod;
		}

		return ret;
	}
}

void modify (int u, int x, int v) {
	if (nd[u].l == nd[u].r) {
		nd[u].sum[0] = nd[u].ans[0] = v;
		nd[u].sum[1] = nd[u].ans[1] = 0;
		return;
	}

	int mid = (nd[u].l + nd[u].r) / 2;
	if (x <= mid)
		modify(lson(u), x, v);
	if (x > mid)
		modify(rson(u), x, v);
	pushup(u);
}

void build_segTree(int u, int l, int r) {
	nd[u].l = l; nd[u].r = r;

	if (l == r) {
		int v = str[(l-1)%N] - '0';
		nd[u].sum[0] = nd[u].ans[0] = v;
		nd[u].sum[1] = nd[u].ans[1] = 0;
		return ;
	}

	int mid = (l + r) / 2;
	build_segTree(lson(u), l, mid);
	build_segTree(rson(u), mid + 1, r);
	pushup(u);
}
