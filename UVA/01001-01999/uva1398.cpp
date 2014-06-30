#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 100005;
const int INF = 0x3f3f3f3f;
const int LCM = 2520;

struct state {
	int v, k;
}s[2 * N];

int n, w, h, c, l, r;

void judge(int x, int p, int tmp) {
	if (p == 0) {
		if (x <= 0 || x >= tmp) r = 0;
	} else if (p > 0) {
		l = max(l, -x * LCM / p);
		r = min(r, (-x + tmp) * LCM / p);
	} else {
		l = max(l, (tmp - x) * LCM / p);
		r = min(r, -x * LCM / p);
	}
}

bool cmp(const state& a, const state& b) {
	if (a.v != b.v) return a.v < b.v;
	return a.k < b.k;
}

void init() {
	c = 0;
	scanf("%d%d%d", &w, &h, &n);

	int x, y, p, q;
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d%d", &x, &y, &p, &q);
		l = 0, r = INF;
		judge(x, p, w);
		judge(y, q, h);
		if (l < r) {
			s[c].v = l; s[c++].k = 1;
			s[c].v = r; s[c++].k = -1;
		}
	}
	sort(s, s + c, cmp);
}

int solve() {
	int ans = 0, g = 0;
	for (int i = 0; i < c; i++) {
		g += s[i].k;
		ans = max(ans, g);
	}
	return ans;
}

int main() {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}
