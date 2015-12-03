#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5;
const int mod = 1e9 + 7;
const ll pmod = 2LL * (mod-1);

int cp, pri[maxn], vis[maxn];
vector<int> G[maxn];

void presolve () {
	cp = 0;
	for (int i = 2; i < maxn; i++) {
		if (vis[i]) continue;
		pri[++cp] = i;
		for (int j = i + i; j < maxn; j += i)
			vis[j] = 1;
	}

	for (int i = 1; i < maxn; i++) {
		int n = i;
		for (int j = 1; j <= cp && pri[j] <= n; j++) {
			while (n % pri[j] == 0) {
				G[i].push_back(j);
				n /= pri[j];
			}
		}
	}
}

int N;
ll C[maxn], L[maxn], R[maxn];

ll pow_mod(ll x, ll n) {
	ll ret = 1;
	while (n) {
		if (n&1) ret = ret * x % mod;
		x = x * x % mod;
		n >>= 1;
	}
	return ret;
}

void solve (int n, int x) {
	for (int i = 0; i < G[n].size(); i++) {
		int v = G[n][i];
		C[v] = (C[v] + x) % pmod;
	}
}

void init () {
	int x;
	memset(C, 0, sizeof(C));
	for (int i = 1; i <= N; i++) {
		scanf("%d", &x);
		solve(i, x);
	}

	int p = 1;
	while (pri[p] < N) p++;
	N = p;

	L[0] = R[N+1] = 1;
	for (int i = 1; i <= N; i++) L[i] = L[i-1] * (C[i] + 1) % pmod;
	for (int i = N; i; i--) R[i] = R[i+1] * (C[i] + 1) % pmod;
}

int main () {
	presolve();
	while (scanf("%d", &N) == 1) {
		init();

		ll ans = 1;
		for (int i = 1; i <= N; i++) {
			ll k = L[i-1] * R[i+1] % pmod;
			ll n = C[i] * (C[i] + 1) / 2 % pmod;
			ans = ans * pow_mod(pri[i], n * k % pmod) % mod;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
