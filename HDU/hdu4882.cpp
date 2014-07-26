#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5+5;
typedef __int64 ll;

struct state {
	ll e, k;
}s[maxn];
int n;

bool cmp (const state& a, const state &b) {
	return a.e * b.k < a.k * b.e;
}

int main () {
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; i++)
			scanf("%I64d", &s[i].e);
		for (int i = 0; i < n; i++)
			scanf("%I64d", &s[i].k);
		sort(s, s + n, cmp);

		ll ans = 0, t = 0;
		for (int i = 0; i < n; i++) {
			t += s[i].e;
			ans += s[i].k * t;
		}

		printf("%I64d\n", ans);
	}
	return 0;
}
