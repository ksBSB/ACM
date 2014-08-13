#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef unsigned long long ll;
const ll MOD = 1LL<<32;
const int maxn = 500000;

ll f[maxn+5], s[maxn+5];

void init () {
	memset(f, 0, sizeof(f));

	s[0] = f[1] = 0;
	for (int i = 1; i <= maxn; i++) {

		for (int k = 1; k * i <= maxn; k++) {
			f[k*i] += (1LL + k) * k / 2;
			f[k*i] %= MOD;
		}
		f[i] = f[i] * i % MOD;
	}

	for (ll i = 1; i <= maxn; i++)
		s[i] = (s[i-1] + f[i]) % MOD;
}

int main () {
	init();
	int cas, n;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%d", &n);
		printf("Case #%d: %I64u\n", kcas, s[n]);
		//printf("Case #%d: %lld\n", kcas, s[n]);
	}
	return 0;
}
