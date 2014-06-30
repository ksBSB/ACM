#include <stdio.h>
#include <string.h>

const int N = 500005;
typedef long long ll;
int n, g[N], f[N];

ll Msort(int l, int r, int* a, int* b) {
	if (r - l == 1) return 0;

	int m = (l + r) / 2;
	ll ans = Msort(l, m, a, b) + Msort(m, r, a, b);
	int p = l, q = m, c = l;
	while (p < m || q < r) {
		if (q >= r || (p < m &&  a[p] <= a[q])) b[c++] = a[p++];
		else {
			ans += m - p;
			b[c++] = a[q++];
		}
	}
	for (int i = l; i < r; i++) a[i] = b[i];
	return ans;
}

int main() {
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; i++) scanf("%d", &g[i]);
		printf("%lld\n", Msort(0, n, g, f));
	}
	return 0;
}
