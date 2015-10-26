#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

int bitcount(ll s) { 
	int c = 0;
	while (s) {
		if (s&1) c++;
		s >>= 1;
	}
	return c;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		int l, r;
		ll s;
		scanf("%lld%d%d", &s, &l, &r);
		s++;
		while (true) {
			int n = bitcount(s);
			if (l <= n && n <= r) break;

			if (n < l) {
				int x = 0;
				while (s&(1LL<<x)) x++;
				s |= (1LL<<x);
			} else {
				ll x = s&(-s);
				s += x;
			}
		}
		printf("Case #%d: %lld\n", kcas, s);
	}
	return 0;
}
