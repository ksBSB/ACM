#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 100005;

struct state {
	int s, t, d;
}p[N];
int n;

bool cmp(const state& a, const state& b) {
	return a.s + a.d < b.s + b.d;
}

void init() {
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &p[i].s, &p[i].t);
		p[i].d = (p[i].t - p[i].s) / 2 + 1;
	}
	sort(p, p + n, cmp);
}

bool judge() {
	int tmp = 0;
	for (int i = 0; i < n; i++) {
		tmp = max(tmp, p[i].s) + p[i].d;
		if (tmp > p[i].t) return false;
	}
	return true;
}

int main() {
	while (scanf("%d", &n) == 1 && n) {
		init();
		printf("%s\n", judge() ? "YES" : "NO");
	}
	return 0;
}
