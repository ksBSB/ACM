#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 105;
const int M = N * N;

ll c[N], d;
char str[M];

inline bool isDight (char ch) {
	return ch >= '0' && ch <= '9';
}

void init () {

	memset(c, 0, sizeof(c));

	ll k = 0, a = 0, key = 0, sign = 1;
	d = 0;

	int len  = strlen(str);
	for (int i = 0; i <= len; i++) {
		if (isDight(str[i])) {
			if (key == 0) {
				a = a * 10 + str[i] - '0';
			} else if (key == 1) {
				k = k * 10 + str[i] - '0';
			} else if (key == 2) {
				d = d * 10 + str[i] - '0';
			}

		} else if (str[i] == '/') {
			key = 2;
		} else if (str[i] == 'n') {
			key = 1;
		} else if (str[i] == '-' || str[i] == '+' || str[i] == ')') {

			if (key >= 1) {
				if (k == 0)
					k = 1;

				if (a == 0)
					a = 1;
			}

			c[k] = a * sign;

			if (str[i] == '-')
				sign = -1;
			else
				sign = 1;

			key = a = k = 0;
		}
	}
}

ll power(ll x, int n, ll MOD) {
	ll ans = 1;
	while (n) {
		if (n&1)
			ans = (ans * x) % MOD;
		x = (x * x) % MOD;
		n /= 2;
	}
	return ans;
}

bool judge () {
	int n = N-1;
	while (c[n] == 0)
		n--;

	/*
	for (int i = 0; i <= n; i++) {
		if (c[i])
			printf("%d %lld\n", i, c[i]);
	}
	*/

	for (ll i = 1; i <= n+1; i++) {

		ll ans = 0;
		for (int j = 0; j <= n; j++) {
			if (c[j])
				ans = (ans + c[j] * power(i, j, d)) % d;
			ans = (ans + d) % d;
		}

		if (ans)
			return false;
	}

	return true;
}

int main () {
	int cas = 1;
	while (scanf("%s", str) == 1 && strcmp(".", str) != 0) {
		init();
		printf("Case %d: %s\n", cas++, judge() ? "Always an integer" : "Not always an integer");
	}
	return 0;
}
