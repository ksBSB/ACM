#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1e5+5;

ll k;
int n, s[maxn], t[maxn];

ll merge_sort (int l, int r, int* a, int* b) {

	if (l == r)
		return 0;

	int mid = (l + r) / 2;
	ll ret = merge_sort(l, mid, a, b) + merge_sort(mid+1, r, a, b);
	int mvl = l, mvr = mid+1, mv = l;
	while (mvl <= mid || mvr <= r) {
		if (mvr > r || (mvl <= mid && a[mvl] <= a[mvr])) {
			b[mv++] = a[mvl++];
		} else {
			ret += mid - mvl + 1;
			b[mv++] = a[mvr++];
		}
	}

	for (int i = l; i <= r; i++)
		a[i] = b[i];
	return ret;
}

int main () {
	while (scanf("%d%I64d", &n, &k) == 2) {
		for (int i = 1; i <= n; i++)
			scanf("%d", &s[i]);
		ll ans = merge_sort(1, n, s, t);
		printf("%I64d\n", max(ans - k, 0LL));
	}
	return 0;
}
