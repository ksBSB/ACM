#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1005;

ll n, r[maxn], l[maxn];

void init () {
	scanf("%lld", &n);
	int x;
	memset(l, 0, sizeof(l));
	memset(r, 0, sizeof(r));

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			scanf("%d", &x);
			if (x) {
				r[i]++;
				r[j]++;
			} else {
				l[i]++;
				l[j]++;
			}
		}
	}
}

ll solve () {
	ll sum = (ll)n * (n-1) * (n-2) / 6;

	ll del = 0;
	for (int i = 0; i < n; i++)
		del += l[i] * r[i];
	return sum - del / 2;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%lld\n", solve());
	}
	return 0;
}
