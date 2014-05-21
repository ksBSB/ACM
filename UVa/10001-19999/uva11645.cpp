#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 100;
const ll M = 1e13;

ll bit (int k) {
	return (ll)1<<k;
}

void add (ll& p, ll& q, ll a, ll b) {
	if (a <= 0 || b <= 0)
		return;

	q += a * b;
	p += q/M;
	q %= M;
}

void solve (ll n) {

	int j = 0;
	ll left = n/2, right = 0;
	ll p = 0, q = 0;

	while (left) {

		left /= 2;
		add(p, q, left, bit(j));
		if ((n&bit(j)) && (n&bit(j+1)))
			add(p, q, 1, right+1);

		if (n&bit(j))
			right |= bit(j);
		j++;
	}

	if (p) {
		printf("%lld", p);
		printf("%013lld\n", q);
	} else {
		printf("%lld\n", q);
	}
}

int main () {
	ll n;
	int cas = 1;
	while (scanf("%lld", &n) == 1 && n >= 0) {
		printf("Case %d: ", cas++);
		solve(n);
	}
	return 0;
}
