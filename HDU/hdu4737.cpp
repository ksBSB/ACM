#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 100005;

int c[35], arr[maxn];

int add (int x, int v) {
	int ret = 0;
	for (int i = 0; i <= 30; i++) {
		if (x&(1<<i))
			c[i] += v;

		if (c[i])
			ret |= (1<<i);
	}
	return ret;
}

ll solve () {
	ll ret = 0;
	memset(c, 0, sizeof(c));
	int l = 0, n, m, x, s = 0;

	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
		s = add(arr[i], 1);

		while (s >= m)
			s = add(arr[l++], -1);
		ret += (i - l + 1);
	}
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		ll ans = solve();
		printf("Case #%d: %I64d\n", kcas, ans);
	}
	return 0;
}
