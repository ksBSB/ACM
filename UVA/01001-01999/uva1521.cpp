#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 10000;

int N, v[maxn];
int npri, vis[maxn+5], prime[maxn+5];

void prime_table (int n) {
	npri = 0;
	for (int i = 2; i <= n; i++) {
		if (vis[i])
			continue;

		prime[npri++] = i;
		for (int j = i * i; j <= n; j += i)
			vis[j] = 1;
	}
}

void set (int u, int x) {

	for (int i = x; i >= 0; i--) {
		int k = prime[i];
		if (v[k] || k > u)
			continue;

		v[k] = 1;
		set(u/k, i-1);
		return;
	}
}

int solve () {
	int ans = 0;
	memset(v, 0, sizeof(v));

	for (int i = npri-1; i >= 0; i--) {
		int u = prime[i];

		if (v[u] || u > N)
			continue;

		ans++;
		v[u] = 1;

		set(N/u, i-1);
	}

	return ans;
}

int main () {
	prime_table(maxn);
	while (scanf("%d", &N) == 1) {
		printf("%d\n", solve());
	}
	return 0;
}
