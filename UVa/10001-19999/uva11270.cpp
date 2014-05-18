#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

int n, m;
ll dp[2][(1<<11)+5];

int main () {
	while (scanf("%d%d", &n, &m) == 2) {
		int now = 0, pre = 1;

		if (n < m)
			swap(n, m);

		int e = (1<<m)-1;
		memset(dp[now], 0, sizeof(dp[now]));

		dp[now][e] = 1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				swap(now, pre);
				memset(dp[now], 0, sizeof(dp[now]));

				for (int s = 0; s <= e; s++) {
					if (j && !(s&(1<<(j-1))) && (s&(1<<j)))
						dp[now][s | (1<<(j-1))] += dp[pre][s];
					dp[now][s ^ (1<<j)] += dp[pre][s];
				}
			}
		}
		printf("%lld\n", dp[now][e]);
	}
	return 0;
}
