#include <stdio.h>
#include <string.h>

const int N = 50005;

struct node {
	int l, r, v;
}s[N*3];

void build(int l, int r, int f) {
	if (l != r) {
		int mid = (l + r) / 2;
		build(l, mid, f*2);
		build(mid+1, r, f*2+1);
	}
	s[f].l = l; s[f].r = r; s[f].v = 0;
}

void insert(int l, int r, int val, int f) {
	if (s[f].l != s[f].r) {
		int mid = (s[f].l + s[f].r) / 2;
		if (l <= mid && r > mid) { insert(l, mid, val, f*2); insert(mid+1, r, val, f*2+1); }
		else if (l <= mid && r <= mid) insert(l, r, val, f*2);
		else insert(l, r, val, f*2+1);
	}
	s[f].v += val;
}

int query(int l, int r, int f) {
	if (l == s[f].l && r == s[f].r) return s[f].v;
	int mid = (s[f].l + s[f].r) / 2;
	if (l <= mid && r > mid) return query(l, mid, f*2) + query(mid+1, r, f*2+1);
	else if (l <= mid && r <= mid) return query(l, r, f*2);
	else return query(l, r, f*2+1);
}

void init () {
	int n, a;
	scanf("%d", &n);
	build(1, n, 1);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a);
		insert(i, i, a, 1);
	}
}

void solve () {
	int a, b;
	char o[20];
	while (scanf("%s", o), strcmp(o, "End")) {
		scanf("%d%d", &a, &b);
		if (o[0] == 'A') insert(a, a, b, 1);
		else if (o[0] == 'S') insert(a, a, -b, 1);
		else printf("%d\n", query(a, b, 1));
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		printf("Case %d:\n", i);
		init();
		solve();
	}
	return 0;
}
