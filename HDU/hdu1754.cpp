#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int N = 200005;

struct node {
	int l, r, v;
}s[N*3];

int n, m;

void build(int l, int r, int f) {
	if (l != r) {
		int mid = (l + r) / 2;
		build(l, mid, 2*f);
		build(mid+1, r, 2*f+1);
	}
	s[f].l = l; s[f].r = r; s[f].v = 0;
}

int insert(int l, int r, int val, int f) {
	if (s[f].l == s[f].r) {
		s[f].v = val; return val;
	} else {
		int mid = (s[f].l + s[f].r) / 2, c;
		if (l <= mid && r > mid) { s[f].v = max(insert(l, mid, val, f*2), insert(mid+1, r, val, f*2+1)); }
		else if (l <= mid && r <= mid) s[f].v = max(insert(l, r, val, f*2), s[f*2+1].v);
		else s[f].v = max(insert(l, r, val, f*2+1), s[f*2].v);
		return s[f].v;
	}
}

int query(int l, int r, int f) {
	if (s[f].l == l && s[f].r == r) return s[f].v;
	int mid = (s[f].l + s[f].r) / 2;
	if (l <= mid && r > mid) return max(query(l, mid, f*2), query(mid+1, r, f*2+1));
	else if (l <= mid && r <= mid) return query(l, r, f*2);
	else return query(l, r, f*2+1);
}

void init() {
	build(1, n, 1);
	int a;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a);
		insert(i, i, a, 1);
	}
}

int main() {
	int a, b;
	char o[10];
	while (scanf("%d%d", &n, &m) == 2) {
		init();
		for (int i = 0; i < m; i++) {
			scanf("%s%d%d", o, &a, &b);
			if (o[0] == 'Q') printf("%d\n", query(a, b, 1));
			else insert(a, a, b, 1);
		}
	}
	return 0;
}
