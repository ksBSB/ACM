#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 5;

struct Pi {
	int idx, l, r;
	bool operator < (const Pi& u) const {
		if (l != u.l)
			return l < u.l;
		return r < u.r;
	}
}p[maxn];

struct State {
	int pos, idx;
	State (int pos = 0, int idx = 0) : pos(pos), idx(idx) {}
	bool operator < (const State& u) const {
		return pos > u.pos;
	}
};
int N, order[maxn];

void init () {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &p[i].l);
		p[i].idx = i;
	}

	for (int i = 1; i <= N; i++)
		scanf("%d", &p[i].r);
	sort(p + 1, p + 1 + N);
}

void solve () {
	int mv = 1, ans = 0;
	priority_queue<State> Q;

	for (int i = 1; i <= N; i++) {
		if (p[i].l <= ans) {
			Q.push(State(p[i].r, p[i].idx));
			continue;
		} else {

			while (!Q.empty() && Q.top().pos < ans) {
				order[mv++] = Q.top().idx;
				Q.pop();
			}

			if (!Q.empty() && Q.top().pos >= ans) {
				order[mv++] = Q.top().idx;
				Q.pop();
				ans++;
				i--;
			} else
				order[mv++] = p[i].idx;
		}
	}

	while (!Q.empty()) {
		if (Q.top().pos >= ans)
			ans++;
		order[mv++] = Q.top().idx;
		Q.pop();
	}

	printf("%d\n", ans);
	for (int i = 1; i <= N; i++)
		printf("%d%c", order[i], i == N ? '\n' : ' ');
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		solve();
	}
	return 0;
}
