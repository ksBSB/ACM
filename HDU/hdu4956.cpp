#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

ll l, r;

bool check (ll u) {
	int sign = 1;
	ll sum = 0;

	while (u) {
		sum += sign * (u % 10);
		sign *= -1;
		u /= 10;
	}

	return sum != 3;
}

void solve () {
	for (ll i = l; i <= r; i++)
		if (i % 11 == 3 && check(i)) {
			printf("%I64d\n", i);
			return;
		}
	printf("-1\n");
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%I64d%I64d", &l, &r);
		solve();
	}
	return 0;
}
