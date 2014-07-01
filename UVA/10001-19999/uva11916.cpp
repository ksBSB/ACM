#include <cstdio>
#include <cstring>
#include <cmath>
#include <set>
#include <map>
#include <algorithm>

using namespace std;
typedef long long ll;
const ll MOD = 1e8+7;
const int maxn = 505;

int N, M, K, R, B, X[maxn], Y[maxn];
set<pair<int, int> > bset;

inline ll mul_mod (ll a, ll b) {
	return (ll)a * b % MOD;
}

inline ll pow_mod (ll a, ll n) {
	ll ans = 1;
	while (n) {
		if (n&1)
			ans = mul_mod(ans, a);
		a = mul_mod(a, a);
		n /= 2;
	}
	return ans;
}

void gcd (ll a, ll b, ll& d, ll& x, ll& y) {
	if (!b) {
		d = a;
		x = 1;
		y = 0;
	} else {
		gcd (b, a%b, d, y, x);
		y -= x * (a/b);
	}
}

inline ll inv (ll a) {
	ll d, x, y;
	gcd(a, MOD, d, x, y);
	return d == 1 ? (x+MOD)%MOD : -1;
}

void init () {
	scanf("%d%d%d%d", &N, &K, &B, &R);
	bset.clear();
	M = 1;
	for (int i = 0; i < B; i++) {
		scanf("%d%d", &X[i], &Y[i]);

		M = max(M, X[i]);

		bset.insert(make_pair(X[i], Y[i]));
	}
}

int count () {
	int c = 0;
	for (int i = 0; i < B; i++) {
		if (X[i] != M && !bset.count(make_pair(X[i]+1, Y[i])))
			c++;
	}

	c += N;
	for (int i = 0; i < B; i++)
		if (X[i] == 1)
			c--;

	return mul_mod(pow_mod(K, c), pow_mod(K-1, (ll)M*N-B-c));
}

int log_mod (ll a, ll b) {
	ll m = (ll)sqrt(MOD+0.5), v, e = 1;
	v = inv(pow_mod(a, m));
	map<ll, ll> g;

	g[1] = 0;

	for (ll i = 1; i < m; i++) {
		e = mul_mod(e, a);
		if (!g.count(e))
			g[e] = i;
	}

	for (ll i = 0; i < m; i++) {
		if (g.count(b))
			return i*m+g[b];
		b = mul_mod(b, v);
	}
	return -1;
}

int doit () {
	int cnt = count();

	if (cnt == R)
		return M;

	int c = 0;
	for (int i = 0; i < B; i++)
		if (X[i] == M)
			c++;

	M++;
	cnt = mul_mod(cnt, pow_mod(K, c));
	cnt = mul_mod(cnt, pow_mod(K-1, N-c));

	if (cnt == R)
		return M;

	return log_mod(pow_mod(K-1, N), mul_mod(R, inv(cnt))) + M;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		init();
		printf("Case %d: %d\n", i, doit());
	}
	return 0;
}
