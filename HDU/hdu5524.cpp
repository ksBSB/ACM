#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;
typedef unsigned long long ll;

set<ll> g;
ll bit[100];

int main () {
	for (int i = 0; i <= 60; i++) bit[i] = (1LL<<i)-1;

	ll n, a, b;
	while (scanf("%lld", &n) == 1) {
		int d = 0;
		while (bit[d] < n) d++;
		ll a = (1LL<<(d-1)), b = bit[d];
		//printf("%lld %lld %lld\n", a, n, b);
		
		ll s = 0;
		g.clear();
		for (int i = 0; a || b || n; i++) {
			g.insert(bit[i+1] - s);

			if (a != n) {
				g.insert(bit[i+1]);
			}
			if (i && b != n) {
				g.insert(bit[i]);
			}

			if ((n&1) == 0) s += (1LL<<i);

			n>>=1, a>>=1, b>>=1;
		}
		printf("%d\n", (int)g.size());
	}
	return 0;
}
