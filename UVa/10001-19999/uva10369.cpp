#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
using namespace std;
const int N = 505;
const int M = 250005;

struct state {
	double dis;
	int l;
	int r;
}s[M];;

int n, m,  cnt, f[N], x[N], y[N];
double ans;

int getfather(int c) {
	return c == f[c] ? c : f[c] = getfather(f[c]);
}

void init() {
	cnt = 0;
	scanf("%d%d", &m, &n);
	for (int i = 0; i < n; i++) {
		f[i] = i; // Init f;
		scanf("%d%d", &x[i], &y[i]);
		for (int j = 0; j < i; j++) {
			s[cnt].dis = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * ( y[i] - y[j]));
			s[cnt].l = i;
			s[cnt].r = j;
			cnt++;
		}
	}
}

bool cmp(const state& a, const state& b) {
	return b.dis - a.dis > 1e-9;
}

void kruskal() {
	sort(s, s + cnt, cmp);;
	int t = n - m - 1;
	for (int i = 0; i < cnt; i++) {
		int p = getfather(s[i].l), q = getfather(s[i].r);
		if (p != q) {
			ans = s[i].dis;
			if (t) {
				t--;
				f[q] = p;
			}
			else
				return ;
		}
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		kruskal();
		printf("%.2lf\n", ans);
	}
	return 0;
}
