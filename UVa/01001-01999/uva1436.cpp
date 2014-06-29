#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int N = 500005;
typedef long long ll;

int P = 0, prime[N], ispri[N];
int n, f[N], vis[N], cnt[N];
ll mod;

void getPrime (int N) {
	memset(ispri, 0, sizeof(ispri));
	for (int i = 2; i < N; i++) {
		if (ispri[i])
			continue;

		prime[P++] = i;
		for (int j = 2 * i; j < N; j += i)
			ispri[j] = 1;
	}
}

void getNode () {
	memset(cnt, 0, sizeof(cnt));

	queue<int> que;
	for (int i = 1; i <= n; i++)
		if (vis[i] == 0)
			que.push(i);

	while (!que.empty()) {
		int u = que.front();
		que.pop();

		cnt[u]++;

		int v = f[u];
		cnt[v] += cnt[u];
		vis[v]--;

		if (vis[v] == 0)
			que.push(v);
	}
}

void init () {
	memset(vis, 0, sizeof(vis));
	scanf("%d%lld", &n, &mod);
	
	f[1] = 0;
	for (int i = 2; i <= n; i++) {
		scanf("%d", &f[i]);
		vis[f[i]]++;
	}
	getNode();

	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; i++)
		vis[cnt[i]]++;
}

ll power (ll x, ll m) {
	ll ans = 1;
	while (m) {
		if (m&1)
			ans = ans * x % mod;

		x = x * x % mod;
		m /= 2;
	}
	return ans;
}

void cal (int u, int v) {
	for (int i = 0; i < P; i++) {
		int k = prime[i];

		while (u % k == 0) {
			cnt[k] += v;
			u /= k;
		}

		if (ispri[u] == 0) {
			cnt[u] += v;
			return;
		}
	}
}

ll solve () {
	memset(cnt, 0, sizeof(cnt));

	for (int i = 2; i <= n; i++)
		cal(i, 1);

	for (int i = 2; i <= n; i++)
		if (vis[i])
			cal(i, -vis[i]);

	ll ans = 1;
	for (int i = 0; i < P; i++) {
		ll u = prime[i];
		if (cnt[u])
			ans = (ans * power(u, cnt[u])) % mod;
	}
	return ans;
}

int main () {
	getPrime(N);

	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%lld\n", solve());
	}
	return 0;
}
