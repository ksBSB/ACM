#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 5;
const int mod = 1e9 + 7;

struct Element {
	int val, pos;
	bool operator < (const Element& u) const { if (val != u.val) return val < u.val; return pos < u.pos; }
}E[maxn];

int N, P[maxn];

int solve () {
	int ret = 0, del;
	sort(E, E + N);
	for (int i = 0; i < N; i++) {
		if (i == 0 || E[i].val != E[i-1].val) del = 0;

		int l = E[i].pos, r = N-E[i].pos-1;
		ret = (ret + 1LL * (P[l] - del + mod) * P[r] % mod * E[i].val % mod) % mod;
		del = (del + P[l]) % mod;
	}
	return ret;
}

int main () {
	P[0] = 1;
	for (int i = 1; i <= (int)1e5; i++) P[i] = P[i-1] * 2 % mod;

	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%d", &E[i].val);
			E[i].pos = i;
		}

		printf("%d\n", solve());
	}
	return 0;
}
