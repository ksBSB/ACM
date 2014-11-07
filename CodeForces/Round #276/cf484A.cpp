#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;
ll l, r;

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%lld%lld", &l, &r);
		ll ans = (1LL<<62)-1;

		for (int i = 61; i >= 0; i--) {
			if (r >= ans && ans >= l)
				break;
			if ((ans^(1LL<<i)) < l)
				continue;
			ans ^= (1LL<<i);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
