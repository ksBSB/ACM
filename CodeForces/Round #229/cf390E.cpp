#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;
const int N = 4 * 1000005;

int n[2], w;
ll bit1[2][N], bit2[2][N];

void insert(ll* b, int m, int x, ll value) {
	while (x <= m) {
		b[x] += value;
		x += x & (-x);
	}
}

ll get(ll* b, int x) {
	ll ans = 0;
	while (x > 0) {
		ans += b[x];
		x -= x & (-x);
	}
	return ans;
}

ll Get(int id, int r) {
	return get(bit1[id], r) * r + get(bit2[id], r);
}

void Insert(int id, int l, int r, ll value) {
	insert(bit1[id], n[id], l, value);
	insert(bit1[id], n[id], r+1, -value);
	insert(bit2[id], n[id], l, -value * (l-1));
	insert(bit2[id], n[id], r+1, value * r);
}

int main () {
	int x1, x2, y1, y2, v;
	scanf("%d%d%d", &n[0], &n[1], &w);
	while (w--) {
		scanf("%d%d%d%d%d", &v, &x1, &y1, &x2, &y2);
		if (v) {
			ll ans = Get(1, y2) - Get(1, y1-1) - (Get(0, n[0]) - Get(0, x2) + Get(0, x1-1));
			cout << ans << endl;
		} else {
			ll value;
			cin >> value;
			Insert(0, x1, x2, value * (y2-y1+1));
			Insert(1, y1, y2, value * (x2-x1+1));
		}
	}
	return 0;
}
