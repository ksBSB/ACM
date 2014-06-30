#include <cstdio>
#include <cstring>

const int N = 30;
typedef long long ll;

ll f[N], b[N];

void init () {
	int n = 26;
	b[1] = b[2] = 1;
	for (int i = 3; i <= n; i++)
		b[i] = b[i-1] * (4*i-6) / i;

	f[1] = f[2] = 1;
	for (int i = 3; i <= n; i++)
		f[i] = (3 * (2 * i - 3) * f[i-1] - (i - 3) * f[i-2])/i;
}

int main () {
	init();
	int n;
	while (scanf("%d", &n) == 1) {
		printf("%lld\n", f[n] - b[n]);
	}
	return 0;
}
