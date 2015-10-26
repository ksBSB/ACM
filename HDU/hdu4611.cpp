#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

int N, A, B;

ll get(ll p) {
	int a = p % A;
	int b = p % B;
	return a > b ? a - b : b - a;
}

ll solve (ll n) {
	ll ret = 0,  p = 0, a = A, b = B, v;
	while (p < n) {
		if (a < b) {
			v = a;
			a += A;
		} else {
			v = b;
			b += B;
		}
		v = min(n, v);
		ret += get(p) * (v - p);
		p = v;
	}
	return ret;
}

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a%b); }

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d%d", &N, &A, &B);
		ll t = 1LL * A / gcd(A, B) * B;
		ll k = N / t;
		ll ans = solve(N - k * t) + solve(t) * k;
		printf("%lld\n", ans);
	}
	return 0;
}
