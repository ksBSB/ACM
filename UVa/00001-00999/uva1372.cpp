#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 5005;

int n, k, x[N];

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d", &n, &k);
		for (int i = 1; i <= n; i++)
			scanf("%d", &x[i]);
		sort(x+1, x+n+1);

		int i = 1;
		int ans = 0;
		while (i <= n) {
			int p = i;
			int cnt = 1;
			while (i < n && (cnt == 1 || x[i+1]-x[i-1] <= k) && x[i+1]-x[i] <= k) {
				i++;
				cnt++;
			}
			if (p == i)
				i++;

			ans = max(ans, cnt);
		}
		printf("%d\n", ans);
	}

	return 0;
}
