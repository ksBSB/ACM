#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;
const int N = 1e5+5;
int n, m, t[N];
ll s;

void find(int k, ll& l, ll& r, int x) {
	l = r = 0;
	for (int i = x-1; i; i--) {
		if ((t[i]&k) == 0) break;
		l++;
	}

	for (int i = x+1; i <= n; i++) {
		if ((t[i]&k) == 0) break;
		r++;
	}
}

void solve (int p, int x, int y) {
	ll l, r;
	for (int i = 0; (1<<i) < N; i++) {
		int k = (1<<i);
		if ((x&k) == (y&k)) continue;

		find(k, l, r, p);
		ll u = (l * r + l + r + 1) * (ll)k;

		if (x&k) {
			s += u;
		} else {
			s -= u;
		}
	}
}

void init () {
	s = 0;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &t[i]);

	for (int i = 0; (1<<i) < N; i++) {
		int k = (1<<i);
		ll c = 0;
		for (int j = 1; j <= n; j++) {
			if (t[j]&k) c++;
			else {
				if (c) s += (c*(c+1)*(ll)k/2);
				c = 0;
			}
		}
		if (c) s += (c*(c+1)*(ll)k/2);
	}
}

int main () {
	init ();
	int p, x;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &p, &x);
		solve (p, x, t[p]);
		t[p] = x;
		cout << s << endl;
	}
	return 0;
}
