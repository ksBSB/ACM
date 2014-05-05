#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>

using namespace std;

const int N = 10005;

struct state {
	int x, y, w, d;
	state() { d = 0; }
	friend bool operator < (state a, state b) {
		return a.y > b.y;
	}
}s[N];
int n, l, r;

bool cmp(const state& a, const state& b) {
	return a.x < b.x;
}

void init() {
	l = 0; r = 10000000;

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d%d%d", &s[i].x, &s[i].y, &s[i].w);
	sort(s, s + n, cmp);
}

bool judge(int c) {
	priority_queue<state> q;
	int cnt = 0, t = 0;
	state k;

	for (int i = 1; i <= 20000; i++) {
		if ( !q.empty()) {
			k = q.top();
			if (k.y + 1 <= i) return false;
		}

		while (t < n) {
			if (s[t].x < i) {
				q.push(s[t]);
				t++;
			} else break;
		}

		int cur = c;
		while (cur && !q.empty()) {
			k = q.top(); q.pop();
			int now = min(cur, k.w - k.d);
			k.d += now; cur -= now;

			if (k.w - k.d) {
				q.push(k);
			} else {
				cnt++;
			}
		}

		if (cnt == n) return true;
	}
	return false;
}

int solve() {
	while (true) {
		if (r - l == 1) break;

		int mid = (l + r) / 2;

		if (judge(mid)) r = mid;
		else l = mid;
	}
	return r;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}
