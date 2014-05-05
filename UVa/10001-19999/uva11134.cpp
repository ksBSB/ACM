#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>

using namespace std;

const int N = 5005;

struct state {
	int l, r, id;
	friend bool operator < (const state a, const state b) {
		return a.r > b.r;
	}
}x[N], y[N], ans[N];
int n;

bool cmp(const state& a, const state& b) {
	return a.l < b.l;
}

void init() {
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d%d", &x[i].l, &y[i].l, &x[i].r, &y[i].r);
		x[i].id = y[i].id = i;
	}
	sort(x, x + n, cmp);
	sort(y, y + n, cmp);
}

bool solve() {
	priority_queue<state> q;
	state c;

	int p = 0;
	for (int i = 0; i < n; i++) {
		while(p < n) {
			if (x[p].l <= i + 1) q.push(x[p]);
			else break;
			p++;
		}

		if (q.empty()) return false;

		c = q.top(); q.pop();
		if (c.r < i + 1) return false;
		ans[c.id].l = i + 1;
	}
	
	p = 0;
	for (int i = 0; i < n; i++) {
		while(p < n) {
			if (y[p].l <= i + 1) q.push(y[p]);
			else break;
			p++;
		}

		if (q.empty()) return false;

		c = q.top(); q.pop();
		if (c.r < i + 1) return false;
		ans[c.id].r = i + 1;
	}

	for (int i = 0; i < n; i++) printf("%d %d\n", ans[i].l, ans[i].r);
	return true;
}

int main () {
	while (scanf("%d", &n) == 1 && n) {
		init();
		if (solve() == false) printf("IMPOSSIBLE\n");
	}
	return 0;
}
