#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

ll pow_mod (ll a, ll n, ll mod) {
	ll ans = 1;
	while (n) {
		if (n&1)
			ans = ans * a % mod;
		a = a * a % mod;
		n /= 2;
	}
	return ans;
}

int legendre (ll a, ll p) {
	a %= p;
	if (a == 0)
		return 0;
	if (pow_mod(a, (p-1)/2, p) == 1)
		return 1;
	else
		return -1;
}

int main () {
	ll a, p;
	while (scanf("%lld%lld", &a, &p) == 2 && a != -1 && p != -1) {
		if (legendre(a, p) < 0)
			printf("No\n");
		else
			printf("Yes\n");
	}
	return 0;
}
