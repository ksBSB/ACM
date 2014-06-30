#include <stdio.h>
#include <string.h>

const int N = 50;
typedef long long ll;

int n;
ll x, y, dp[N];

inline void init () {
	int v[5];
	char s[5];
	memset(v, 0, sizeof(v));

	for (int i = 0; i < 6; i++) {
		scanf("%s", s);
		int u = s[0] - 'A' + 1;
		int k = s[1] - 'A' + 1;

		if (v[u]) continue;

		v[u] = k;
	}

	if (v[2] != 1 && v[3] != 1) {
		x = 3; y = 0;
	} else if (v[v[1]] == 1) {
		x = 3; y = 2;
	} else {
		x = 2; y = 1;
	}
}

int main () {
	while (scanf("%d", &n) == 1) {
		init ();
		dp[1] = 1;
		for (int i = 2; i <= n; i++)
			dp[i] = dp[i-1] * x + y;
		printf("%lld\n", dp[n]);
	}
	return 0;
}
