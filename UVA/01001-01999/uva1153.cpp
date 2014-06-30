#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>

using namespace std;

const int N = 900005;
struct state {
	int q, d;
	friend bool operator < (const state a, const state b) {
		return a.q < b.q;
	}
}s[N];


int n, ans, tmp;

bool cmp(const state& a, const state& b) {
	return a.d < b.d;
}

void init() {
	ans = tmp = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d%d", &s[i].q, &s[i].d);
	sort(s, s + n, cmp);
}

void solve() {
	priority_queue<state> que;
	
	for (int i = 0; i < n; i++) {
		tmp += s[i].q;
		que.push(s[i]);
		ans++;

		if (tmp > s[i].d) {
			state c = que.top(); que.pop();
			ans--;
			tmp -= c.q;
		}
	}
	printf("%d\n", ans);
}

int main() {
	int cas; scanf("%d", &cas);
	while (cas--) {
		init();
		solve();
		if (cas) printf("\n");
	}
	return 0;
}
