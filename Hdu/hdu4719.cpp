#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;
const int N = 1e5+5;

struct state {
	int pos;
	ll high;
}p[N];

struct node {
	int left;
	int right;
	ll val;
}t[N*4];

int n, k;
ll dp[N];

inline ll max(ll a, ll b) {
	return a > b ? a : b;
}

ll BuildTree (int c, int l, int r) {
	t[c].left = l;
	t[c].right = r;

	if (l == r) {
		t[c].val = -1;
	} else {
		int mid = (l + r)/2;
		t[c].val = max(BuildTree(c*2, l, mid), BuildTree(c*2+1, mid+1, r));
	}

	return t[c].val;
}

ll Query (int c, int l, int r) {
	if (l == t[c].left && r == t[c].right)
		return t[c].val;

	int mid = (t[c].left + t[c].right) / 2;
	if (l <= mid && r > mid)
		return max(Query(c*2, l, mid), Query(c*2+1, mid+1, r));
	else if (l <= mid && r <= mid)
		return Query(c*2, l, r);
	else
		return Query(c*2+1, l, r);
}

ll upDate (int c, int l, int r, ll val) {
	if (l == t[c].left && r == t[c].right) {
		t[c].val = val;
		return val;
	}

	int mid = (t[c].left + t[c].right) / 2;
	if (l <= mid && r > mid)
		return t[c].val = max(upDate(c*2, l, mid, val), upDate(c*2+1, mid+1, r, val));
	else if (l <= mid && r <= mid)
		return t[c].val = max(upDate(c*2, l, r, val), t[c*2+1].val);
	else
		return t[c].val = max(t[c*2].val, upDate(c*2+1, l, r, val));
}

inline bool cmp (const state& a, const state& b) {
	if (a.high != b.high)
		return a.high < b.high;
	return a.pos > b.pos;
}

void init () {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) {
		cin >> p[i].high;
		p[i].pos = i;
	}
	sort(p+1, p+n+1, cmp);

	BuildTree(1, 0, n);
}

ll solve () {

	upDate(1, 0, 0, 0);
	for (int i = 1; i <= n; i++) {

		dp[p[i].pos] = -1;
		ll val = Query(1, max(0, p[i].pos-k), p[i].pos-1);
		//cout << val << " " << p[i].pos << endl;

		if (val == -1) 
			continue;

		dp[p[i].pos] = val + p[i].high * p[i].high;

		if (p[i].pos == n)
			break;
		upDate(1, p[i].pos, p[i].pos, dp[p[i].pos] - p[i].high);
	}
	return dp[n];
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		init ();
		cout << "Case #" << i << ": ";

		ll ans = solve();
		if (ans <= 0)
			cout << "No solution" << endl;
		else
			cout << ans << endl;
	}
	return 0;
}
