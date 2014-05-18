#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 205;
const int INF = 0x3f3f3f3f;

int n, k, a[N], b[N];

void init () {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
}

int solve (int l, int r) {
	memcpy(b, a, sizeof(a));

	int ans = 0;
	for (int i = l; i <= r; i++)
		ans += a[i];

	int p, q;
	for (int i = 0; i < k; i++) {
		int bMax = -INF, bMin = INF;
		for (int j = 1; j <= n; j++) {
			if ((j < l || j > r) && b[j] > bMax) {
				bMax = b[j];
				p = j;
			} else if (j >= l && j <= r && b[j] < bMin) {
				bMin = b[j];
				q = j;
			}
		}
		int t = bMax - bMin;
		if (t <= 0)
			break;

		ans += t;
		swap(b[p], b[q]);
	}
	return ans;
}

int main () {
	init();

	int ans = -INF;
	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j++)
			ans = max(ans, solve(i, j));
	}
	printf("%d\n", ans);
	return 0;
}
