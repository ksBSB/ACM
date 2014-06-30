#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

ll n, m, p;

ll qPow (ll a, ll k) {
	ll ans = 1;

	while (k) {
		if (k&1)
			ans = (ans * a) % p;
		a = (a * a) % p;
		k /= 2;
	}
	return ans;
}

/*
long long qPow(long long a, long long k) {  
	if (k == 0) return 1;  
	if (k == 1) return a;  
	long long ans = qPow(a * a % p, k>>1);  
	if (k&1) ans = ans * a % p;
	return ans;  
}  
*/

ll C (ll a, ll b, ll p) {

	if (a < b)
		return 0;

	if (b > a - b)
		b = a - b;

	ll up = 1, down = 1;

	for (ll i = 0; i < b; i++) {
		up = up * (a-i) % p;
		down = down * (i+1) % p;
	}
	return up * qPow(down, p-2) % p;
}

ll lucas (ll a, ll b, ll p) {
	if (b == 0)
		return 1;
	return C(a%p, b%p, p) * lucas(a/p, b/p, p) % p;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%lld%lld%lld", &n, &m, &p);
		printf("%lld\n", lucas(n+m, m, p));
	}
	return 0;
}
