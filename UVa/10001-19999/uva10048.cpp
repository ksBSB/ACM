#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 105;
const int M = 1005;
const int Q = 10005;
struct state {
	int r, l, num;
}s[M];
int n, m, f[N];

int getfather(int x) {
	return x == f[x] ? x : f[x] = getfather(f[x]);
}

bool cmp(const state& a, const state& b) {
	return a.num < b.num;
}

void init() {
	for (int i = 0; i < m; i++)
		scanf("%d%d%d", &s[i].l, &s[i].r, &s[i].num);
	sort(s, s + m, cmp);
}

int kruskal() {
	int a, b;
	scanf("%d%d", &a, &b);
	for (int i = 1; i <= n; i++)
		f[i] = i;
	for (int i = 0; i < m; i++) {
		int p = getfather(s[i].l), q = getfather(s[i].r);
		if (p != q) {
			f[p] = q;
			if (getfather(a) == getfather(b))
				return s[i].num;
		}
	}
	return -1;
}

int main () {
	int cas = 0, q;
	while (scanf("%d%d%d", &n, &m, &q), n || m || q) {
		init();
		if (cas) printf("\n");
		printf("Case #%d\n", ++cas);
		for (int i = 0; i < q; i++) {
			int ans = kruskal();
			if (ans < 0)
				printf("no path\n");
			else
				printf("%d\n", ans);
		}
	}
	return 0;
}
