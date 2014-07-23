#include <cstdio>
#include <cstring>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 50;
const ll mod = 30;

struct state {
	ll s, c;
	state (ll s, ll c) {
		this->s = s;
		this->c = c;
	}
};
int n, k;

inline bool ispos (ll pos, ll s) {
	if (pos >= n)
		return true;
	return !(s & (1<<pos));
}

inline ll cal (char* str, ll pos) {
	ll ans = 0;

	for (int i = 0; i < n; i++) {
		if (str[i] == 'v')
			ans |= (1<<i);
	}
	return ans * mod + pos;
}

ll bfs (ll S) {
	queue<state> que;
	que.push(state(S, 0));

	map<ll, int> g;
	g[S] = 1;

	while (!que.empty()) {
		state u = que.front();
		que.pop();
		//printf("%lld %lld\n", u.s, u.c);

		if (u.s == 0)
			return u.c + 2;

		ll pos = u.s % mod, s = u.s / mod;

		// left;
		if (pos > 0 && ispos(pos + 1, s) ) {
			ll v = s * mod + pos - 1;

			if (!g.count(v)) {
		//		printf("left!\n");
				g[v] = 1;
				que.push(state(v, u.c+1));
			}
		}

		// right;
		if (pos < n-1 && (pos >= n - 2 || (ispos(pos + 2, s) && ispos(pos + 3, s))) ) {
			ll v = s * mod + pos + 1;

			if (!g.count(v)) {
		//		printf("rignt!\n");
				g[v] = 1;
				que.push(state(v, u.c+1));
			}
		}

		if ( pos == n-1 || !ispos(pos+1, s)) {
			ll v = (s^(1<<pos)) * mod + pos;

			if (!g.count(v)) {
		//		printf("change!\n");
				g[v] = 1;
				que.push(state(v, u.c+1));
			}
		}
	}
	return -1;
}

int main () {
	int pos, cas;
	char str[maxn];
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%s%d", &n, str, &pos);
		printf("%lld\n", bfs(cal(str, pos-1)));
	}
	return 0;
}
