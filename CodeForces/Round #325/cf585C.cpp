#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

ll x, y;
vector<ll> ans;

ll gcd (ll a, ll b) {
	if (b == 0) return a;
	ans.push_back(a / b);
	return gcd(b, a % b);
}

int main () {
	ans.clear();
	scanf("%lld%lld", &x, &y);

	ll k = gcd(x, y);
	if (k != 1)
		printf("Impossible\n");
	else {
		int n = ans.size();
		ans[n-1]--;

		int v = x < y;
		for (int i = 0; i < n; i++) {
			if (ans[i] == 0) continue;
			printf("%lld%c", ans[i], 'A' + v);
			v ^= 1;
		}
		printf("\n");
	}
	return 0;
}
