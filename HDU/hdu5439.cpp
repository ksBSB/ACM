#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 500000;
const int mod = 1e9+7;

struct Seg {
	ll l, r, s;
	Seg(ll l = 0, ll r = 0, ll s = 0): l(l), r(r), s(s) {}
}seg[maxn];

int binsearch(int l, int r, int x) {
	while (l < r) {
		int mid = (l + r) >> 1;
		if (x > seg[mid].r) l = mid + 1;
		else r = mid;;
	}
	return l;
}

ll get(ll l, ll r) {
	return (r-l+1)*(r+l) / 2 % mod;
}

void init () {
	seg[1] = Seg(1, 1, 1);
	seg[2] = Seg(2, 3, 11);

	for (int i = 3; i < maxn; i++) {
		int v = binsearch(1, i-1, i);
		ll l = seg[i-1].r+1, r = seg[i-1].r+v;
		seg[i] = Seg(l ,r, (seg[i-1].s + get(l, r) * i % mod) % mod);
	}
}

int solve (int n) {
	int k = binsearch(1, maxn-1, n);
	return (seg[k-1].s + get(seg[k-1].r+1, n) * k % mod) % mod;
}

int main () {
	init();

	int cas, n;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &n);
		printf("%d\n", solve(n));
	}
	return 0;
}
