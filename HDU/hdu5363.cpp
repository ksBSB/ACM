#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int mod = 1000000007;

int pow_mod (long long x, int n) {
	long long ans = 1;
	while (n) {
		if(n&1)
			ans = ans * x % mod;
		x = x * x % mod;
		n >>= 1;
	}
	return ans;
}

int main () {
	int cas, n;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &n);
		printf("%d\n", (pow_mod(2, n-1) + mod - 1) % mod);
	}
	return 0;
}
