#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 1e6;

int ans[maxn+5], vis[maxn*4+5];

void primeTable (int n) {
	memset(vis, 0, sizeof(vis));

	for (int i = 2; i <= n; i++) {
		if (vis[i])
			continue;

		for (int j = 2 * i; j <= n; j += i)
			vis[j] = 1;
	}
}

int main () {
	primeTable(maxn*4);
	ans[1] = 0;
	for (int i = 2; i <= maxn; i++)
		ans[i] = ans[i-1] + (vis[3*i+7] ? 0 : 1);
	int cas, n;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &n);
		printf("%d\n", ans[n]);
	}
	return 0;
}
