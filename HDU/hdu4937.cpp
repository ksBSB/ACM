#include <cstdio>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <set>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1e6;

ll N;
int np, vis[maxn+5], prime[maxn+5];
set<ll> ans;

int c, cnt[maxn+5];
ll nowbase, fact[maxn+5];

void prime_table (int n) {
	np = 0;
	memset(vis, 0, sizeof(vis));

	for (int i = 2; i <= n; i++) {
		if (vis[i])
			continue;

		prime[np++] = i;
		for (int j = 2 * i; j <= n; j += i)
			vis[j] = 1;
	}
}

void div_factor (ll n) {
	c = 0;
	for (int i = 0; i < np && n >= prime[i]; i++) {

		if (n % prime[i] == 0) {

			cnt[c] = 0;
			fact[c] = prime[i];;

			while (n % prime[i] == 0) {
				n /= prime[i];
				cnt[c]++;
			}
			c++;
		}
	}

	if (n != 1) {
		fact[c] = n;
		cnt[c++] = 1;
	}
}

bool judge (ll n, ll base) {

	if (base <= nowbase)
		return false;

	while (n) {
		if (n%base < 3 || n%base > 6)
			return false;
		n /= base;
	}
	ans.insert(base);
	return true;
}

void dfs (int d, ll s, ll u) {

	judge(u/s, s);

	if (d == c)
		return;

	for (int i = 0; i <= cnt[d]; i++) {
		dfs (d+1, s, u);
		s *= fact[d];
	}
}

void solve (ll n) {

	if (n <= 0)
		return;

	div_factor(n);
	dfs(0, 1, n);
}

int main () {
	prime_table(maxn);

	int cas;
	scanf("%d", &cas);

	for (int kcas = 1; kcas <= cas; kcas++) {
		//scanf("%lld", &N);
		scanf("%I64d", &N);

		printf("Case #%d: ", kcas);
		if (N >= 3 && N <= 6)
			printf("-1\n");
		else {
			ans.clear();
			for (int i = 3; i <= 6; i++) {
				nowbase = i;
				solve(N-i);
			}
			int ret = ans.size();
			printf("%d\n", ret);
		}
	}
	return 0;
}
