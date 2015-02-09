#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 2 * 1e6 + 5;
const char sign[3][10] = {"Vanya", "Vova", "Both"};
typedef long long ll;

struct Attack {
	int v;
	ll t;
}att[maxn];

int N;
ll X, Y;

inline ll gcd (ll a, ll b) {
	return b == 0 ? a : gcd(b, a % b);
}

inline bool cmp (const Attack& a, const Attack& b) {
	return a.t < b.t;
}

void solve (int& n, Attack* a, ll p, ll e, int k) {
	ll s = p;
	while (s <= e) {
		a[n++] = (Attack){k, s};
		s += p;
	}
}

int main () {
	scanf("%d%lld%lld", &N, &X, &Y);
	int n = 0, ai;

	ll G = X / gcd(X, Y) * Y;
	solve(n, att, G / X, G, 0);
	solve(n, att, G / Y, G, 1);
	sort(att, att + n, cmp);

	for (int i = 1; i < n; i++) {
		if (att[i].t == att[i-1].t)
			att[i].v = att[i-1].v = 2;
	}

	for (int i = 0; i < N; i++) {
		scanf("%d", &ai);
		ai = (ai - 1) % (X + Y);
		printf("%s\n", sign[att[ai].v]);
	}

	return 0;
}
