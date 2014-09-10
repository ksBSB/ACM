#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define lowbit(x) ((x)&(-x))

using namespace std;
typedef long long ll;
const int maxn = 10005;
const int maxm = 105;
const ll mod = 123456789;

struct state {
	ll val;
	int pos, rank;
	state (ll val = 0, int pos = 0, int rank = 0) {
		this->val = val;
		this->pos = pos;
		this->rank = rank;
	}
};

int N, M, T;
ll dp[maxn][maxm], fenw[maxm][maxn];
vector<state> vec;

inline bool sort_val(const state& a, const state& b) {
	return a.val < b.val;
}

inline bool sort_pos(const state& a, const state& b) {
	return a.pos < b.pos;
}

void add (ll* f, int x, ll v) {
	while (x <= T) {
		f[x] = (f[x] + v) % mod;
		x += lowbit(x);
	}
}

ll sum (ll* f, int x) {
	ll ret = 0;
	while (x) {
		ret = (ret + f[x]) % mod;
		x -= lowbit(x);
	}
	return ret;
}

void init () {

	ll x;
	vec.clear();
	for (int i = 1; i <= N; i++) {
		scanf("%lld", &x);
		vec.push_back(state(x, i));
	}

	sort(vec.begin(), vec.end(), sort_val);

	vec[0].rank = 2;
	for (int i = 1; i < N; i++) {
		vec[i].rank = vec[i-1].rank;
		if (vec[i].val != vec[i-1].val)
			vec[i].rank++;
	}
	T = vec[N-1].rank;

	sort(vec.begin(), vec.end(), sort_pos);
}

ll solve () {
	memset(dp, 0, sizeof(dp));
	memset(fenw, 0, sizeof(fenw));

	add(fenw[0], 1, 1);

	for (int i = 1; i <= N; i++) {
		for (int j = min(i, M); j >= 1; j--) {
			ll tmp = sum(fenw[j-1], vec[i-1].rank - 1);
			dp[i][j] = (dp[i][j] + tmp) % mod;
			add(fenw[j], vec[i-1].rank, tmp);
		}
	}

	ll ret = 0;
	for (int i = 1; i <= N; i++)
		ret = (ret + dp[i][M]) % mod;
	return ret;
}

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		init();
		printf("%lld\n", solve());
	}
	return 0;
}
