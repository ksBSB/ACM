#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 1e5+5;

int n, m;
ll a[N], b[N], c[N*2];

inline ll max(ll a, ll b) {
	return a > b ? a : b;
}

int main () {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%lld", &a[i]);
		c[i] = a[i];
	}

	for (int i = 0; i < m; i++) {
		scanf("%lld", &b[i]);
		c[i+n] = b[i];
	}

	sort(c, c + n + m);

	ll tmp = c[m], ans = 0;

	for (int i = 0; i < n; i++)
		ans += max(0, tmp - a[i]);

	for (int i = 0; i < m; i++)
		ans += max(0, b[i] - tmp);

	printf("%lld\n", ans);
	return 0;
}
