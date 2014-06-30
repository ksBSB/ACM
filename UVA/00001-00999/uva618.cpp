#include <cstdio>
#include <cstring>

const int N = 5;
typedef long long ll;

inline ll gcd (ll a, ll b) {
	return b == 0 ? a : gcd(b, a%b);
}

inline int bitCount(int x) {
	return x == 0 ? 0 : bitCount(x/2) + (x&1);
}

struct state {
	ll r, c;
	state (ll r = 0, ll c = 0) {
		this->r = r;
		this->c = c;
	}
	void get() {
		scanf("%lld%lld", &r, &c);
		ll d = gcd(r, c);
		r /= d;
		c /= d;
	}
}w[N];

bool solve (ll R, ll C, int s);

inline bool cmp (state a, state b) {
	return a.r * b.c == b.r * a.c;
}

void cat (state u, state v, state& a, state& b, int s) {
	ll p, q;
	if (s == 0) {
		ll d = gcd(u.r, v.r);
		p = v.r / d;
		q = u.r / d;
	} else {
		ll d = gcd(u.c, v.c);
		p = v.c / d;
		q = u.c / d;
	}
	a.r = u.r * p;
	a.c = u.c * p;
	b.r = v.r * q;
	b.c = v.c * q;
}

bool judge(ll R, ll C, state v, int s, int sign) {

	if (sign == 0) {

		if (R % v.r)
			return false;

		ll k = R / v.r;
		C -= v.c * k;
		if (C <= 0)
			return false;
	} else {

		if (C % v.c)
			return false;
		
		ll k = C / v.c;
		R -= v.r * k;
		if (R <= 0)
			return false;

	}
	return solve(R, C, s);
}

bool judgeTow(ll R, ll C, state v, int s) {

	for (int i = 0; i < 4; i++) {
		if ((s&(1<<i)) == 0) 
			continue;

		state add, a, b;
		for (int j = 0; j < 2; j++) {
			cat(v, w[i], a, b, j);

			if (j == 0) {
				add.r = a.r;
				add.c = a.c + b.c;
			} else {
				add.r = a.r + b.r;
				add.c = a.c;
			}

			if (judge(R, C, add, s-(1<<i), 1-j))
				return true;
		}
	}
	return false;
}

bool solve (ll R, ll C, int s) {

	int cnt = bitCount(s);

	if (cnt == 1) {

		for (int i = 0; i < 4; i++)
			if (s&(1<<i))
				return cmp(state(R, C), w[i]);
	}

	for (int i = 0; i < 4; i++) {
		if ((s&(1<<i)) == 0)
			continue;

		for (int j = 0; j < 2; j++) {
			if (judge(R, C, w[i], s-(1<<i), j))
				return true;
		}

		if (cnt > 2 && judgeTow(R, C, w[i], s-(1<<i)))
			return true;
	}
	return false;
}

int main () {
	int cas = 1;
	ll R, C;
	while (scanf("%lld%lld", &R, &C) == 2 && R + C) {
		for (int i = 0; i < 4; i++)
			w[i].get();

		printf("Set %d: %s\n", cas++, solve(R, C, 15) ? "Yes" : "No");
	}
	return 0;
}
