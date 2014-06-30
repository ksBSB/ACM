#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;
const int N = 20005;
const ll INF = (1<<31)-1;
struct ad {
	ll a, b, c;
}d[N];
int n, m;
ll l, r;

void init () {
	l = INF; r = 0;

	for (int i = 0; i < n; i++) {
		cin >> d[i].a >> d[i].b >> d[i].c;
		l = min(l, d[i].a);
		r = max(r, d[i].b);
	}
}

ll judge (ll k) {
	ll c = 0;
	for (int i = 0; i < n; i++) {
		ll x = min(r, d[i].b) - d[i].a;
		ll y = min(k, d[i].b) - d[i].a;
		if (x >= 0)
			c += (x/d[i].c + 1);
		if (y >= 0)
			c -= (y/d[i].c + 1);

	}
	return c;
}

ll solve () {
	while (l < r) {
		ll mid = (l+r) / 2;
		if (judge(mid)&1) l = mid+1;
		else r = mid;
	}
	return l;
}

int main () {
	while (scanf("%d", &n) == 1) {
		init ();
		if (judge(l-1)&1) {
			ll ans = solve(), c = 0;
			for (int i = 0; i < n; i++) {
				if (ans > d[i].b) continue;
				ll x = ans - d[i].a;
				if (x >= 0&&x%d[i].c == 0) c++;
			}
			cout << ans << " " << c << endl;
		} else
			printf("DC Qiang is unhappy.\n");
	}
	return 0;
}
