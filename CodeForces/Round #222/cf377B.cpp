#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>

using namespace std;

const int N = 100005;

struct state {
	int id, val, pass;
	friend bool operator <(const state& a, const state& b) {
		return a.pass > b.pass;
	}
}p[N], bug[N];
int n, m, s;

bool cmp(const state& a, const state& b) {
	return a.val > b.val;
}

void init() {
	scanf("%d%d%d", &n, &m, &s);
	for (int i = 0; i < m; i++) {
		scanf("%d", &bug[i].val); bug[i].id = i;
	}
	for (int i = 0; i < n; i++) scanf("%d", &p[i].val);
	for (int i = 0; i < n; i++) {
		scanf("%d", &p[i].pass);
		p[i].id = i;
	}
	sort(p, p + n, cmp);
	sort(bug, bug + m, cmp);
}

bool judge(int k) {
	int a = 0, b = 0, sum = s;
	priority_queue<state> que;
	while (b < m) {
		while (a < n) {
			if (p[a].val >= bug[b].val) que.push(p[a]);
			else break;
			a++;
		}

		if (que.empty()) return false;

		state c = que.top(); que.pop();
		if (sum < c.pass) return false;

		sum -= c.pass;
		b += k;
	}
	return true;	
}

void put(int k) {
	int a = 0, b = 0;
	int ans[N];
	priority_queue<state> que;

	while (b < m) {
		while (a < n) {
			if (p[a].val >= bug[b].val) que.push(p[a]);
			else break;
			a++;
		}

		state c = que.top(); que.pop();

		int t = min(m, b + k);
		for (int i = b; i < t; i++)
			ans[bug[i].id] = c.id + 1;
		b += k;
	}
	printf("%d", ans[0]);
	for (int i = 1; i < m; i++) printf(" %d", ans[i]);
	printf("\n");
}

void solve() {
	if (!judge(m))  {
		printf("NO\n"); return;
	}

	int l = 0, r = m;
	while (l < r) {
		int mid = (l + r) / 2;
		if (judge(mid)) r = mid;
		else l = mid + 1;
	}
	printf("YES\n");
	put(r);
}

int main() {
	init();
	solve();
	return 0;
}
