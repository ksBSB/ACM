#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a%b); }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

ll solve (ll x, ll n) {
	ll d = gcd(x, n - x);
	ll ret = x / d * (n - x);

	while (d != 1 && x > 0) {
		x--;
		d = gcd(x, n - x);
		ret = max(ret, x / d * (n - x));
	}
	return ret;
}

int main () {
	int cas, n;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &n);
		printf("%lld\n", solve(n>>1, n));
	}
	return 0;
}
