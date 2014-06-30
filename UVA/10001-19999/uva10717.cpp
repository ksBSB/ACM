#include <stdio.h>
#include <string.h>
#define min(a,b) (a)<(b)?(a):(b)
#define max(a,b) (a)>(b)?(a):(b)
const int N = 105;
const int INF = 0x3f3f3f3f;
int n, m;
long long coin[N], high[N], l[N], r[N];

void init() {
	for (int i = 0; i < n; i++)
		scanf("%lld", &coin[i]);
	for (int i = 0; i < m; i++)
		scanf("%lld", &high[i]);
	memset(l, 0, sizeof(l));
	memset(r, INF, sizeof(r));
}

long long gcd(long long a, long long b) {
	return b == 0 ? a : gcd(b, a % b);
}

void judge(long long c) {
	for (int i = 0; i < m; i++) {
		long long d = c;
		while (1) {
			if (d == high[i]) {
				l[i] = max(l[i], d);
				r[i] = min(r[i], d);
				break;
			}
			else if (d > high[i]) {
				l[i] = max(l[i], d - c);
				r[i] = min(r[i], d);
				break;
			}
			d += c;
		}
	}
}

void solve() {
	long long c, d;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			d = gcd(coin[i], coin[j]);
			d = coin[i] * coin[j] / d;
			for (int k = j + 1; k < n; k++) {
				for (int t = k + 1; t < n; t++) {
					c = gcd(coin[k], coin[t]);
					c = coin[k] * coin[t] / c;
					long long now = gcd(c, d);
					judge(c * d / now);
				}
			}
		}
	}
}

int main () {
	while (scanf("%d%d", &n, &m), n || m) {
		init();
		solve();
		for (int i = 0; i < m; i++)
			printf("%lld %lld\n", l[i], r[i]);
	}
	return 0;
}
