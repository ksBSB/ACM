#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 50;

int gcd (int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}

int main () {
	int n, t;
	ll p[maxn];
	while (scanf("%d%d", &n, &t) == 2) {
		p[0] = 1;
		for (int i = 1; i <= n; i++)
			p[i] = p[i-1] * t;

		ll a = 0, b = 0;
		for (int i = 0; i < n; i++)
			a += p[gcd(n, i)];

		if (n&1)
			b = n * p[(n+1)/2];
		else
			b = n / 2 * (p[n/2+1] + p[n/2]);
		printf("%lld %lld\n", a / n, (a + b) / 2 / n);
	}
	return 0;
}