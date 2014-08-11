#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 60;

ll gcd (ll a, ll b) {
	return b == 0 ? a : gcd(b, a % b);
}

int main () {
	ll f[maxn];
	f[0] = 1;
	for (int i = 1; i <= 50; i++)
		f[i] = f[i-1] * 2;

	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		int N, K;
		scanf("%d%d", &N, &K);

		printf("Case #%d: ", kcas);
		if (K == 1)
			printf("0/1\n");
		else {
			ll member = f[K] - K - 1;
			ll d = gcd(member, f[K]);
			printf("%lld/%lld\n", member / d, f[K] / d);
		}
			
	}
	return 0;
}
