#include <stdio.h>
#include <string.h>
#include <math.h>
const int N = 1000010;

bool vis[N];

long long gcd(long long a, long long b) {
	return b == 0 ? a : gcd(b, a % b);
}

int main () {
	long long a, b, c, n, cntans, cntuse;
	while (scanf("%lld", &n) == 1) {
		cntans = cntuse = 0;
		memset(vis, 0, sizeof(vis));
		long long m = (long long)sqrt(n + 0.5);
		for (long long t = 1; t <= m; t += 2) {
			for (long long s = t + 1; s * t <= n; s += 2) {
				if (gcd(s, t) == 1) {
					a = s * t * 2;
					b = (s * s - t * t);
					c = (s * s + t * t);
					if (c <= n) {
						cntans++;
						if (!vis[a]) { cntuse++; vis[a] = 1; }
						if (!vis[b]) { cntuse++; vis[b] = 1; }
						if (!vis[c]) { cntuse++; vis[c] = 1; }
					}

					for (int i = 2; c * i <= n; i++) {
						if (!vis[a * i]) { cntuse++; vis[a * i] = 1; }
						if (!vis[b * i]) { cntuse++; vis[b * i] = 1; }
						if (!vis[c * i]) { cntuse++; vis[c * i] = 1; }
					}
				}
			}
		}
		printf("%lld %lld\n", cntans, n - cntuse);
	}
	return 0;
}
