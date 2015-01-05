#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 10000;

int np, pri[maxn+5], vis[maxn+5];

void prime_table(int n) {

	np = 0;
	memset(vis, 0, sizeof(vis));
	vis[0] = vis[1] = 1;

	for (int i = 2; i <= n; i++) {
		if (vis[i])
			continue;

		pri[np++] = i;
		for (int j = i * i; j <= n; j += i)
			vis[j] = 1;
	}
}

int main () {
	int n;
	prime_table(maxn);
	while (scanf("%d", &n) == 1) {
		int ans = 0;
		for (int i = 0; i < np; i++) {
			for (int j = i; j < np; j++) {
				if (pri[i] + pri[j] >= n)
					break;
				int t = n - pri[i] - pri[j];

				if (vis[t] == 0 && t >= pri[j])
					ans++;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
