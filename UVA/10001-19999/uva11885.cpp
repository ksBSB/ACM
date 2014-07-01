#include <cstdio>
#include <cstring>

typedef long long ll;
const ll MOD = 987654321;

void mul(ll a[2][2], ll b[2][2], ll c[2][2]) {
	ll ans[2][2];
	memset(ans, 0, sizeof(ans));

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			
			for (int k = 0; k < 2; k++)
				ans[i][j] = (ans[i][j] + a[i][k] * b[k][j]) % MOD;
		}
	}
	memcpy(c, ans, sizeof(ans));
}

void power (ll a[2][2], int n) {
	ll ans[2][2] = {1, 0, 1, 0};
	while (n) {
		if (n&1)
			mul(ans, a, ans);
		mul(a, a, a);
		n /= 2;
	}
	memcpy(a, ans, sizeof(ans));
}

int main () {
	int p;
	while (scanf("%d", &p) == 1 && p) {
		if (p&1 || p < 6) {
			printf("0\n");
			continue;
		}

		p = (p - 4) / 2;

		ll a[2][2] = {1, 1, 1, 0};
		/*
		power(a, 2*p-1);
		printf("%lld\n", (a[0][0] + a[0][1]  - p - 1 + MOD) % MOD);
		*/
		power(a, 2*p);
		printf("%lld\n", (a[1][0] - p - 1 + MOD) % MOD);
	}
	return 0;
}
