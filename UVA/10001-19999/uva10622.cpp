#include <cstdio>
#include <cstring>
#include <cmath>

const int maxp = 333333;
int cp, v[maxp], prime[maxp];

int gcd (int a, int b) {
	return b == 0 ? a : gcd(b, a%b);
}

void primeTable (int n) {

	memset(v, 0, sizeof(v));

	cp = 0;
	for (int i = 2; i < n; i++) {
		if (!v[i]) {
			prime[cp++] = i;

			for (int j = 2 * i; j < n; j += i)
				v[j] = 1;
		}
	}
}

int divFactor (long long n) {
	int ans = 0;

	for (int i = 0; i < cp && prime[i] <= n; i++) {
		if (n % prime[i] == 0) {
			int cnt = 0;
			while (n % prime[i] == 0) {
				n /= prime[i];
				cnt++;
			}
			ans = gcd(ans, cnt);
		}
	}

	if (n > 1 || ans == 0)
		ans = 1;
	return ans;
}

int main () {
	primeTable(maxp);
	long long n;
	while (scanf("%lld", &n) == 1 && n) {
		int ans = divFactor(n < 0 ? -n : n);	
		if (n < 0) {
			while (ans%2 == 0)
				ans /= 2;
		}
		printf("%d\n", ans);
	}
	return 0;
}
