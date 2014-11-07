#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
ll l, r;

ll gcd(ll a, ll b) {
	return b == 0 ? a : gcd(b, a % b);
}

bool solve() {
	for (ll a = l; a <= r; a++) {
		for (ll b = a + 1; b <= r; b++) {
			for (ll c = b + 1; c <= r; c++)
				if (gcd(a, b) == 1 && gcd(b, c) == 1 && gcd(a, c) != 1) {
					printf("%lld %lld %lld\n", a, b, c);
					return false;
				}
		}
	}
	return true;
}

int main () {
	scanf("%lld%lld", &l, &r);
	if (solve())
		printf("-1\n");
	return 0;
}
