#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e6;
typedef long long ll;

ll N;
int tot, num[maxn+5];
int np, prime[maxn+5], vis[maxn+5];
int nf, fact[maxn+5], cnt[maxn+5];

void prime_table (int n) {
	np = 0;
	for (int i = 2; i <= n; i++) {
		if (vis[i])
			continue;
		prime[np++] = i;
		for (int j = i * 2; j <= n; j += i)
			vis[j] = 1;
	}
}

void div_factor (ll n) {
	nf = 0;
	memset(cnt, 0, sizeof(cnt));

	for (int i = 0; i < np; i++) {
		if (n % prime[i] == 0) {
			fact[nf] = prime[i];
			while (n % prime[i] == 0) {
				n /= prime[i];
				cnt[nf]++;
			}
			nf++;
		}
	}

	if (n > 1) {
		fact[nf] = n;
		cnt[nf++] = 1;
	}
}

void dfs (int d, ll u) {
	if (u > 1000000LL)
		return;

	if (d == nf) {
		num[tot++] = u;
		return;
	}

	for (int i = 0; i <= cnt[d]; i++) {
		dfs(d+1, u);
		u *= fact[d];
	}
}

ll gcd (ll a, ll b) {
	return b == 0 ? a : gcd(b, a % b);
}

ll lcm (ll a, ll b) {
	ll d = gcd(a, b);
	return a / d * b;
}

int main () {
	int cas = 1;
	prime_table(maxn);
	while (scanf("%lld", &N) == 1 && N) {

		int ret = tot = 0;

		printf("Scenario %d:\n", cas++);

		div_factor(N);
		dfs(0, 1);
		sort(num, num + tot);

		for (int i = 0; i < tot; i++) {
			for (int j = i + 1; j < tot; j++) {
				if (num[j] - num[i] > 25)
					break;
				ll d = lcm(num[i], num[j]);

				for (int k = j + 1; k < tot; k++) {
					if (num[k] - num[i] > 25)
						break;

					if (lcm(d, num[k]) == N) {
						printf("%d %d %d\n", num[i], num[j], num[k]);
						ret++;
					}
				}
			}
		}

		if (ret == 0)
			printf("Such bells don't exist\n");
		printf("\n");
	}
	return 0;
}
