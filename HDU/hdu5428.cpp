#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int inf = (1<<31)-1;
const int maxn = 1e9;
const int maxm = 1e6;

int N, ans[2];
int P, prime[maxm + 5], vis[maxm + 5];

void init () {
	P = 0;
	memset(vis, 0, sizeof(vis));
	for (int i = 2; i * i <= maxn; i++) {
		if (vis[i]) continue;
		prime[P++] = i;
		for (int j = i + i; 1LL * j * j <= maxn; j += i)
			vis[j] = 1;
	}
}

void maintain(int x) {
	if (ans[0] > x) swap(ans[0], x);
	if (ans[1] > x) swap(ans[1], x);
}

void solve () {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < P; i++) {
		if (n % prime[i] == 0) {
			while (n % prime[i] == 0) {
				maintain(prime[i]);
				n /= prime[i];
			}
		}
	}

	if (n != 1) maintain(n);
}

int main () {
	init();
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &N);
		ans[0] = ans[1] = inf;

		for (int i = 0; i < N; i++)
			solve();

		if (ans[1] == inf) printf("-1\n");
		else printf("%lld\n", 1LL * ans[0] * ans[1]);
	}
	return 0;
}
