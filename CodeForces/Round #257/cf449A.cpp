#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
ll n, m, k;

ll gao (ll x, ll y) {
	ll a = n / (x + 1);
	a = min(a, n - a * x);
	ll b = m / (y + 1);
	b = min(b, m - b * y);
	return a * b;
}

ll solve () {
	if (n + m - 2 < k)
		return -1;
	ll x = max(k - n + 1, 0LL);
	ll y = max(k - m + 1, 0LL);
	return max(gao(k - x, x), gao(y, k - y));
}

int main () {
	scanf("%lld%lld%lld", &n, &m, &k);
	printf("%lld\n", solve());
	return 0;
}
