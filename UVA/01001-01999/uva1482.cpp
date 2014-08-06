#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

ll SG (ll x) {
	return x&1 ? SG(x>>1) : x>>1;
}

int main () {
	int cas, n;

	scanf("%d", &cas);
	while (cas--) {
		ll m, v = 0;
		scanf("%d", &n);

		for (int i = 0; i < n; i++) {
			scanf("%lld", &m);
			v ^= SG(m);
		}
		printf("%s\n", v ? "YES" : "NO");
	}
	return 0;
}
