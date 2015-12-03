#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;
typedef set<int>::iterator iter;
typedef long long ll;
const int maxn = 1005;
const int mod = 1e9 + 7;

int C(int x) { return 1LL * x * (x+1) / 2 % mod; }

struct Point {
	int x, y;
	bool operator < (const Point& u) const { return x < u.x; }
}P[maxn];

int N, M, K;
set<int> pos;

void add(int y, ll& s) {
	iter it = pos.upper_bound(y);
	iter rf = it;
	it--;

	if (*it == y) return;

	s = (s - C(*rf - *it - 1) + mod) % mod;
	s = (s + C(*rf - y - 1) + C(y - *it - 1)) % mod;
	pos.insert(y);
}

ll solve(int s) {
	pos.clear();
	pos.insert(0);
	pos.insert(M+1);

	ll ret = 0, sum = C(M), l = P[s].x - P[s-1].x;

	add(P[s].y, sum);
	for (int i = s+1; i <= K; i++) {
		if (P[i].x != P[i-1].x) {
			int r = P[i].x - P[i-1].x;
			ret = (ret + sum * l % mod * r % mod) % mod;
		}
		add(P[i].y, sum);
	}
	int r = N + 1 - P[K].x;
	ret = (ret + sum * l % mod * r % mod) % mod;
	return ret;
}

int main () {
	while (scanf("%d%d%d", &N, &M, &K) == 3) {
		for (int i = 1; i <= K; i++) scanf("%d%d", &P[i].x, &P[i].y);
		P[0].x = 0, P[K+1].x = N+1;
		sort(P + 1, P + K + 1);

		ll ans = 0;
		for (int i = 1; i <= K + 1; i++)
			ans = (ans + C(P[i].x - P[i-1].x - 1)) % mod;
		ans = ans * C(M) % mod;

		for (int i = 1; i <= K; i++)
			ans = (ans + solve(i)) % mod;
		ans = (1LL * C(N) * C(M) % mod - ans + mod) % mod;
		printf("%lld\n", ans);
	}
	return 0;
}
