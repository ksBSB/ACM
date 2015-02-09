#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5;
ll ans[maxn] = {0, 1};

int pow_mod(ll x, int n, int mod) {
	ll ret = 1;
	while (n) {
		if (n&1)
			ret = ret * x % mod;
		x = x * x % mod;
		n >>= 1;
	}
	return ret;
}

int inv (int a, int n) {
	return pow_mod(a, n-2, n);
}

int main () {
	int n;
	scanf("%d", &n);
	if (n == 1)
		printf("YES\n1\n");
	else if (n == 4)
		printf("YES\n1\n3\n2\n4\n");
	else {
		for (int i = 2; i < n; i++) {
			ans[i] = inv(i, n);
			if (n % i == 0) {
				printf("NO\n");
				return 0;
			}
		}
		printf("YES\n1\n");
		for (int i = 2; i < n; i++)
			printf("%lld\n", ans[i-1] * i % n);
		printf("%d\n", n);
	}
	return 0;
}
