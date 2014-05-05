#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 105;

struct house {
	int x, y, w, d, h, id;
	void get(int f) {
		scanf("%d%d%d%d%d", &x, &y, &w, &d, &h);
		id = f;
	}
}p[N], q[N];
int n;

bool cmp(const house& a, const house& b) {
	if (a.x != b.x) return a.x < b.x;
	return a.y < b.y;
}

bool judge (int k) {
	int cn = 0;
	for (int i = 0; i < n; i++) {
		if (i == k || p[i].y >= p[k].y) continue;
		if (p[i].x >= p[k].x + p[k].w) continue;
		if (p[i].x + p[i].w <= p[k].x) continue;
		if (p[k].h > p[i].h) continue;
		q[cn++] = p[i];
	}
	if (cn == 0) return true;
	int tmp = p[k].x;
	sort(q, q + cn, cmp);
	for (int i = 0; i < cn; i++) {
		if (tmp < q[i].x) return true;
		tmp = max(tmp, q[i].x + q[i].w);
	}
	return tmp < p[k].x + p[k].w;
}

void solve () {
	sort(p, p + n, cmp);
	int flag = 0;
	for (int i = 0; i < n; i++) if (judge(i)) {
		if (flag++) printf(" ");
		printf("%d", p[i].id);
	}
	printf("\n");
}

int main () {
	int cas = 0;
	while (scanf("%d", &n) == 1 && n) {
		if (cas) printf("\n");
		for (int i = 0; i < n; i++) p[i].get(i+1);
		printf("For map #%d, the visible buildings are numbered as follows:\n", ++cas);
		solve();
	}
	return 0;
}
