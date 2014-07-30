#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

#define lson(x) ((x<<1))
#define rson(x) ((x<<1)|1)

using namespace std;
typedef __int64 ll;

const int maxn = 100005;
const int maxf = 100;
const ll INF = 2000000000000000LL;

int n, m;
ll fib[maxf], fn, num[maxn];

struct maxnode {
	int l, r;
	ll sum;
	bool isfib;

	void set (int l, int r, ll sum, bool isfib) {
		this->l = l;
		this->r = r;
		this->sum = sum;
		this->isfib = isfib;
	}
} node[4 * maxn];

void init () {
	fib[0] = fib[1] = 1;
	for (fn = 2;; fn++) {
		fib[fn] = fib[fn - 2] + fib[fn - 1];
		if (fib[fn] > INF)
			break;
	} 
}

void pushup(int x) {
	int l = lson(x), r = rson(x);

	node[x].isfib = (node[l].isfib && node[r].isfib);
	node[x].sum = node[l].sum + node[r].sum;;
}

void build(int l, int r, int x) {
	node[x].set(l, r, 0, false);

	if (l == r)
		return;

	int mid = (l + r) / 2;

	build(l, mid, lson(x));
	build(mid + 1, r, rson(x));
}

ll find (ll x) {
	int id;
	ll ans = INF;
	for (int i = 0; i < fn; i++) {
		ll k = (fib[i] > x ? fib[i] - x : x - fib[i]);
		if (k < ans) {
			ans = k;
			id = i;
		}
	}
	return fib[id];
}

void add (int k, ll v, int x) {

	if (node[x].l == k && node[x].r == k) {
		node[x].sum += v;
		node[x].isfib = (find(node[x].sum) == node[x].sum ? true : false);
		return;
	}

	int mid = (node[x].l + node[x].r) / 2;
	if (k <= mid)
		add(k, v, lson(x));
	else if (k > mid)
		add(k, v, rson(x));
	pushup(x);
}

void insert(int l, int r, int x) {

	if (node[x].isfib)
		return;

	if (node[x].l == node[x].r) {
		node[x].sum = find(node[x].sum);
		node[x].isfib = true;
		return;
	}

	int mid = (node[x].l + node[x].r) / 2;
	if (l <= mid)
		insert(l, r, lson(x));
	if (r > mid)
		insert(l, r, rson(x));
	pushup(x);
}

ll query(int l, int r, int x) {

	if (node[x].l >= l && node[x].r <= r)
		return node[x].sum;

	int mid = (node[x].l + node[x].r) / 2;

	ll ans = 0;
	if (l <= mid)
		ans += query(l, r, lson(x));
	if (r > mid)
		ans += query(l, r, rson(x));
	return ans;
}

int main() {
	init();

	while (scanf("%d%d", &n, &m) == 2) {
		build(1, n, 1);

		int Q, a, b;
		ll v;

		while (m--) {
			scanf("%d", &Q);
			if (Q == 1) {
				scanf("%d%I64d", &a, &v);
				add(a, v, 1);
			} else if (Q == 2) {
				scanf("%d%d", &a, &b);
				printf("%I64d\n", query(a, b, 1));
			} else {
				scanf("%d%d", &a, &b);
				insert(a, b, 1);
			}
		}
	}
	return 0;
}
