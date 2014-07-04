#include <cstdio>
#include <cstring>

const int maxn = 1e6+5;
typedef long long ll;

int v[maxn], prime[maxn], cp;

void primeHtable(int n) {
	cp = 0;
	memset(v, 0, sizeof(v));

	for (int i = 5; i < n; i += 4) {
		if (v[i])
			continue;

		prime[cp++] = i;
		for (int j = i * 2; j < n; j += i)
			v[j] = 1;
	}
}

int solve (int n) {
	int ans = 0;
	memset(v, 0, sizeof(v));

	for (int i = 0; prime[i] < n && i < cp; i++) {
		if ((ll)prime[i] * prime[i] > n)
			break;

		for (int j = i; prime[j] < n && j < cp; j++) {

			ll u = (ll)prime[i] * prime[j];
			if (u > n)
				break;


			if (v[u])
				continue;
			ans++;
			v[u] = 1;
		}
	}
	return ans;
}

int main () {
	primeHtable(maxn);
	int n;
	while (scanf("%d", &n) == 1 && n) {
		printf("%d %d\n", n, solve(n));
	}
	return 0;
}
