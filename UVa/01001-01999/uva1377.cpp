#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;
const int N = 50;
const int M = 100005;
typedef set<int>::iterator iter;

struct state {
	int s, now;
	set<int> rec;
}ans;
int n, c, d[N], v[M];

void init() {
	c = 0; 
	ans.rec.clear();
	memset(v, 0, sizeof(v));
	int a;
	for (int i = 0; i < n; i++) {
		scanf("%d", &a);
		if (!v[a]) {
			d[c++] = a;
			v[a] = 1;
		}
	}
	sort(d, d + c);
	memset(v, -1, sizeof(v));
	for (int i = 0; i < c; i++) v[d[i]] = i;
}

bool cmp(state a, state b) {
	if (a.rec.size() != b.rec.size()) return a.rec.size() > b.rec.size();
	iter p = a.rec.begin(), q = b.rec.begin();
	while (p != a.rec.end()) {
		if (*p != *q) return *p > *q;
		p++; q++;
	}
	return false;
}

state add(state u, int k) {
	for (iter i = u.rec.begin(); i != u.rec.end(); i++) {
		int t = abs(*i - k);
		if (v[t] == -1) continue;
		if ((u.s & (1<<v[t])) == 0) u.s += (1<<v[t]); 
	}
	u.rec.insert(k);
	return u;
}

void bfs() {
	int tmp = (1 << c) - 1, m = d[c-1];
	state u;
	queue<state> que;
	u.s = 0; u.rec.insert(0);
	que.push(u);

	while (!que.empty()) {
		u = que.front(); que.pop();

		if (ans.rec.size() != 0 && ans.rec.size() < u.rec.size()) return;
		if (u.s == tmp) {
			if (ans.rec.size() == 0 || cmp(ans, u)) ans = u;
		} else {
			if (u.rec.size() == 7) continue;
			for (int i = 0; i < c; i++) if ((u.s & (1<<i)) == 0) {
				for (iter j = u.rec.begin(); j != u.rec.end(); j++) {
					if (*j + d[i] <= m) que.push(add(u, *j + d[i]));
					if (*j > d[i]) que.push(add(u, *j - d[i]));
				}
				break;
			}
		}
	}
}

void solve() {
	bfs();
	int flag = false;
	printf("%lu\n", ans.rec.size());
	for (iter i = ans.rec.begin(); i != ans.rec.end(); i++) {
		if (flag) printf(" ");
		printf("%d", *i); flag = true;
	}
	printf("\n");
}

int main() {
	int cas = 1;
	while (scanf("%d", &n) == 1 && n) {
		init();
		printf("Case %d:\n", cas++);
		solve();
	}	
	return 0;
}
