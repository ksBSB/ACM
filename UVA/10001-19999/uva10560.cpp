#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
typedef unsigned long long ll;

ll n, S;
vector<ll> ans;

void init (ll n) {
	S = 0;
	ans.clear();

	while (S < n) {
		ll u = S * 2 + 1;
		ans.push_back(u);
		S += u;
	}
	printf("%lu", ans.size());
	for (int i = 0; i < ans.size(); i++)
		printf(" %lld", ans[i]);
	printf("\n");
}

void solve () {
	ll k, s = S;
	scanf("%lld", &k);

	int sign = 1, flag = 0;
	for (int i = ans.size() - 1; i >= 0; i--) {
		ll t = (s - 1) / 3;

		s -= ans[i];
	//	printf("%lld %lld %lld\n", ans[i], s, k);
		if (k <= t)
			continue;

		if (flag) 
			printf("%c", sign > 0 ? '+' : '-');

		if (k < ans[i]) {
			sign *= -1;
			k = ans[i] - k;
		} else {
			k = k - ans[i];
		}
		flag = 1;
		printf("%lld", ans[i]);
	}
	printf("\n");
}

int main () {
	int k;
	while (scanf("%lld%d", &n, &k) == 2 && n + k) {
		init(n);
		for (int i = 0; i < k; i++)
			solve();
	}
	return 0;
}
