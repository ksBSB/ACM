#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 1e5 + 5;

ll n, x, c[N];

int main () {
	ll ans = 0;

	scanf("%lld%lld", &n, &x);
	for (int i = 0; i < n; i++)
		scanf("%lld", &c[i]);

	sort(c, c + n);

	for (int i = 0; i < n; i++) {
		ans += c[i] * x;

		if (x > 1)
			x--;
	}
	printf("%lld\n", ans);
	return 0;
}
