#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

ll gcd (ll a, ll b) {
	return b == 0 ? a : gcd(b, a % b);
}

int main () {
	int cas;
	ll n, m;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%lld%lld", &n, &m);
		printf("Case %d: %lld\n", kcas, (n + m) / gcd(n, m));
	}
	return 0;
}
