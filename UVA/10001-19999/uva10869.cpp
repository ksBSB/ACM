#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>

#define lowbit(x) ((x)&(-x))

using namespace std;
const int maxn = 200000;

set<int> vec;
int ans;
int N, R, C, fenx[maxn+5], rec[maxn+5];
int cntx[maxn+5], cnty[maxn+5], have[maxn+5];

struct point {
	int x, y;
	int rx, ry;
}p[maxn+5];

inline bool sort_y (const point& a, const point& b) {
	return a.y < b.y;
}

inline bool sort_xby (const point& a, const point& b) {
	if (a.x != b.x)
		return a.x < b.x;
	return a.y > b.y;
}

inline bool sort_xsy (const point& a, const point& b) {
	if (a.x != b.x)
		return a.x > b.x;
	return a.y < b.y;
}

void add_treeArr (int x, int val) {
	while (x <= maxn) {
		fenx[x] += val;
		x += lowbit(x);
	}
}

int query_treeArr (int x) {
	int ret = 0;
	while (x) {
		ret += fenx[x];
		x -= lowbit(x);
	}
	return ret;
}

void init () {
	memset(cntx, 0, sizeof(cntx));
	memset(cnty, 0, sizeof(cnty));
	memset(fenx, 0, sizeof(fenx));

	for (int i = 0; i < N; i++)
		scanf("%d%d", &p[i].x, &p[i].y);

	sort(p, p + N, sort_y);
	C = p[0].ry = 1;
	add_treeArr(C, 1);
	for (int i = 1; i < N; i++) {
		if (p[i].y != p[i-1].y)
			C++;
		p[i].ry = C;
		add_treeArr(C, 1);
	}

	sort(p, p + N, sort_xby);
	R = p[0].rx = 0;
	for (int i = 1; i < N; i++) {
		if (p[i].x != p[i-1].x)
			R++;
		p[i].rx = R;
	}
}

void set_ans (int ret, set<int> v) {
	if (ret > ans) {
		ans = ret;
		vec.clear();
	}

	if (ret == ans) {
		for (set<int>::iterator i = v.begin(); i != v.end(); i++)
			vec.insert(N - ret - cntx[p[*i].rx] - cnty[p[*i].ry] + 1);
	}
}

void solve () {
	memcpy(rec, fenx, sizeof(fenx));

	for (int i = 0; i < N; i++) {
		have[i] = query_treeArr(C) - query_treeArr(p[i].ry);
		add_treeArr(p[i].ry, -1);
		cntx[p[i].rx]++;
		cnty[p[i].ry]++;
	}

	ans = 0;
	vec.clear();
	memcpy(fenx, rec, sizeof(rec));

	int pre = p[N-1].rx, ret = N;
	set<int> oll;
	for (int i = N-1; i >= 0; i--) {
		int tmp = have[i] + query_treeArr(p[i].ry - 1);
		add_treeArr(p[i].ry, -1);

		if (p[i].rx != pre) {
			set_ans(ret, oll);
			pre = p[i].rx;

			ret = N;
			oll.clear();
		}

		if (ret > tmp) {
			ret = tmp;
			oll.clear();
		}

		if (ret == tmp)
			oll.insert(i);
	}
	set_ans(ret, oll);

	printf("Stan: %d; Ollie:", ans);
	for (set<int>::iterator i = vec.begin(); i != vec.end(); i++)
		printf(" %d", *i);
	printf(";\n");
}

int main () {
	while (scanf("%d", &N) == 1 && N) {
		init();
		solve();
	}
	return 0;
}
