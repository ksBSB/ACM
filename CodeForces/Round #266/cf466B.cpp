#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int main () {
	bool flag = false;
	ll n, a, b, ans = INF, l, r;

	scanf("%lld%lld%lld", &n, &a, &b);
	n *= 6;

	if (a > b) {
		swap(a, b);
		flag = true;
	}

	for (ll i = 1; i <= n; i++) {
		ll x = i, y = (n - 1) / i + 1;
		if (x > y)
			break;
		x = max(x, a);
		y = max(y, b);
		if (x * y < ans) {
			ans = x * y;
			l = x;
			r = y;
		}
	}

	if (flag)
		swap(l, r);

	printf("%lld\n%lld %lld\n", ans, l, r);
	return 0;
}
