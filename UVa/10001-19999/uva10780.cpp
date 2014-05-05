#include <stdio.h>
#include <string.h>
#include <math.h>

#define min(a,b) (a)<(b)?(a):(b)

const int N = 10005;
const int INF = 0x3f3f3f3f;

int n, m, c[N];

void div (int k) {
	int t = ceil(sqrt(k));
	for (int i = 2; i <= k && i <= t; i++) {
		while (k % i == 0) {
			c[i]++;
			k /= i;
		}
	}
	c[k]++;
}

void solve () {
	int i;
	memset(c, 0, sizeof(c));

	for (i = 2; i <= n; i++)
		div(i);

	int ans = INF, t = ceil(sqrt(m));
	for (i = 2; i <= m && i <= t; i++) {
		if (m%i == 0) {
			int cnt = 0;
			while (m % i == 0) {
				cnt++;
				m /= i;
			}
			ans = min (ans, c[i]/cnt);
		}
	}
	if (m != 1)
		ans = min(ans, c[m]);

	if (ans == INF || ans == 0) 
		printf("Impossible to divide\n");
	else 
		printf("%d\n", ans);
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		scanf("%d%d", &m, &n);
		printf("Case %d:\n", i);
		solve ();
	}
	return 0;
}