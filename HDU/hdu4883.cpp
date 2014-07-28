#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 10005;

struct state {
	int pos, val;
	void set (int pos, int val) {
		this->pos = pos;
		this->val = val;
	}
}s[maxn * 2];

int n;

bool cmp (const state& a, const state& b) {
	if (a.pos != b.pos)
		return a.pos < b.pos;
	return a.val < b.val;
}

void init () {
	scanf("%d", &n);
	int x, h1, m1, h2, m2;
	for (int i = 0; i < n; i++) {
		scanf("%d%d:%d%d:%d", &x, &h1, &m1, &h2, &m2);
		s[i*2].set(h1 * 60 + m1, x);
		s[i*2+1].set(h2 * 60 + m2, -x);
	}
	sort(s, s+2*n, cmp);
}

int solve () {
	int ans = 0, tmp = 0;
	int mv = 0;
	for (int i = 0; i < 2 * n; i++) {
		tmp += s[i].val;
		ans = max(ans, tmp);
	}
	return ans;
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
