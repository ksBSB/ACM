#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
using namespace std;
const int N = 760;;
const int M = 600000;

struct state {
	double dis;
	int l;
	int r;
}s[M];;

int n, cnt, f[N], x[N], y[N];

int getfather(int c) {
	return c == f[c] ? c : f[c] = getfather(f[c]);
}

double add(int i, int j) {
	s[cnt].dis = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * ( y[i] - y[j]));
	s[cnt].l = i;
	s[cnt].r = j;
	cnt++;
}

void init() {
	cnt = 0;
	for (int i = 0; i < n; i++) {
		f[i] = i; // Init f;
		scanf("%d%d", &x[i], &y[i]);
		for (int j = 0; j < i; j++)
			add(i, j);
	}

	int m, a, b;
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &a, &b);
		int p = getfather(a - 1), q = getfather(b - 1);
		if (p != q)
			f[q] = p;
	}
}

bool cmp(const state& a, const state& b) {
	return b.dis - a.dis > 1e-9;
}

double kruskal() {
	sort(s, s + cnt, cmp);;
	double sum = 0;
	for (int i = 0; i < cnt; i++) {
		int p = getfather(s[i].l), q = getfather(s[i].r);
		if (p != q) {
			f[q] = p;
			sum += s[i].dis;
		}
	}
	return sum;
}

int main () {
	while (scanf("%d", &n) == 1) {
		init();
		printf("%.2lf\n", kruskal());
	}
	return 0;
}
