#include <cstdio>
#include <cstring>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef set<pii>::iterator iter;

ll ans;
set<pii> G;

ll get(ll x, ll y) { return x * x + y * y; }

void solve (ll x, ll y) {
	iter it = G.lower_bound(make_pair(x, y));

	for (iter i = it; i != G.end(); i++) {
		ll tmp = i->first - x;
		if (tmp * tmp >= ans) break;
		ans = min(ans, get(i->first - x, i->second - y));
	}

	for (iter i = it; i != G.begin();) {
		i--;
		ll tmp = x - i->first;
		if (tmp * tmp >= ans) break;
		ans = min(ans, get(i->first - x, i->second - y));
	}
}

int main () {
	int cas, n;
	scanf("%d", &cas);
	while (cas--) {
		G.clear();
		scanf("%d", &n);
		ll Ax, Bx, Cx;
		ll Ay, By, Cy;
		scanf("%lld%lld%lld", &Ax, &Bx, &Cx);
		scanf("%lld%lld%lld", &Ay, &By, &Cy);

		ans = 1e18;
		ll x = Bx % Cx, y = By % Cy, ret = 0;

		for (int i = 1; i < n; i++) {
			G.insert(make_pair(x, y));
			x = (x * Ax + Bx) % Cx;
			y = (y * Ay + By) % Cy;
			solve(x, y);
			ret += ans;
		}
		printf("%lld\n", ret);
	}
	return 0;
}
