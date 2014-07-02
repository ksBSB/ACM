#include <cstdio>
#include <cstring>
#include <cmath>

const int maxn = 1e6;
typedef long long ll;

int cp, v[maxn+5];
ll limit, prime[maxn+5];

void primeTable (int n) {
	cp = 0;
	memset(v, 0, sizeof(v));	

	for (int i = 2; i <= n; i++) {
		if (v[i])
			continue;

		prime[cp++] = i;
		for (int j = 2 * i; j <= n; j += i)
			v[j] = 1;
	}
}

inline ll cal(ll a, ll b) {
	ll k = b / a;
	if (b%a)
		k++;

	if (k * a <= limit && v[k*a] == 0)
		k++;
	return k * a;
}

int cnt, set[maxn+5], vis[maxn+5];
ll L, R;

void solve () {
	memset(vis, 0, sizeof(vis));

	ll m = sqrt(R+0.5);

	for (int i = 0; i < cp; i++) {

		if (prime[i] > m)
			break;

		for (ll j = cal(prime[i], L); j <= R; j += prime[i]) {
			vis[j-L] = 1;
		}
	}

	cnt = 0;
	for (ll i = L; i <= R; i++) {
		if (i == 1 || i == 0)
			continue;

		if (vis[i-L])
			continue;
		set[cnt++] = i-L;
	}
}

int main () {
	limit = 1<<16;
	primeTable(limit);
	while (scanf("%lld%lld", &L, &R) == 2) {
		solve();

		if (cnt <= 1)
			printf("There are no adjacent primes.\n");
		else {
			int minRec, maxRec, minDis, maxDis;
			maxDis = 0;
			minDis = 1e7;

			for (int i = 1; i < cnt; i++) {
				int tmp = set[i] - set[i-1];

				if (tmp > maxDis) {
					maxDis = tmp;
					maxRec = i;
				}

				if (tmp < minDis) {
					minDis = tmp;
					minRec = i;
				}
			}
			printf("%lld,%lld are closest, %lld,%lld are most distant.\n", set[minRec-1]+L, set[minRec]+L, set[maxRec-1]+L, set[maxRec]+L);
		}
	}
	return 0;
}
