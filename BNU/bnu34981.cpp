#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int N = 1e5+5;

bool flag;
int n, m, c, mv, f[N], r[N], ans[N];
vector<int> g[N];

int getfar(int x) {
	return x == f[x] ? x : f[x] = getfar(f[x]);
}

void init () {
	scanf("%d%d", &n, &m);

	flag = false;
	for (int i = 0; i <= n; i++)
		r[i] = f[i] = i;
	for (int i = 0; i < m; i++)
		g[i].clear();

	int t;
	for (int i = 0; i < m; i++) {
		scanf("%d", &t);
		int a, pre = 0;

		for (int j = 0; j < t; j++) {
			scanf("%d", &a);
			g[i].push_back(a);
			if (a < pre)
				flag = true;
			pre = a;
		}
	}
}

bool insert (int x, int d) {

	for (int j = mv-1; j >= 0; j--) {
		if (g[d][j] < x) {
			int p = getfar(g[d][j]);
			f[p] = x;
			r[p] = x;
			mv = j;
			return true;
		}
	}
	return false;
}

void put(int x) {
	ans[c--] = x;
	if (r[x] != x)
		put(r[x]);
}

void solve () {

	for (int i = m-1; i; i--) {
		int t = g[i].size();

		mv = g[i-1].size();

		for (int j = t-1; j >= 0; j--)
			if (!insert(g[i][j], i-1)) {
				flag = true;
				return;
			}
	}

	c = n;
	int t = g[0].size();
	for (int i = t-1; i >= 0; i--)
		put(g[0][i]);
}

int main () {
	int cas; 
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		init ();

		printf("Case #%d: ", i);
		solve();

		if (flag) {
			printf("No solution\n");
		} else {
			for (int j = 1; j < n; j++)
				printf("%d ", ans[j]);
			printf("%d\n", ans[n]);
		}
	}
	return 0;
}
