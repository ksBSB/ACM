#include <stdio.h>
#include <string.h>
#include <vector>
#include <set>

using namespace std;
const int N = 1e6+5;

struct edge {
	int u, v;
	edge (int u, int v) {
		this->u = u;
		this->v = v;
	}

	friend bool operator < (const edge& a, const edge& b) {
		if (a.u != b.u) return a.u < b.u;
		return a.v < b.v;
	}
};

int n, f[N];
vector<edge> g;
set<int> vis;

int getfar (int x) {
	return x == f[x] ? x : f[x] = getfar(f[x]);
}

bool init () {
	int a, b;
	n = 0;
	g.clear();
	vis.clear();

	while (scanf("%d%d", &a, &b) == 2 && a + b) {
		if (a == -1 && b == -1) return false;
		n = max(n, max(a, b));
		g.push_back(edge(a, b));
		vis.insert(a);
		vis.insert(b);
	}

	for (int i = 0; i <= n; i++)
		f[i] = i;
	return true;
}

bool judge () {

	for (int i = 0; i < g.size(); i++) {
		int a = g[i].u, b = g[i].v;
		int p = getfar(a), q = getfar(b);
		if (p == q) return false;
		f[q] = p;
	}

	int tmp = getfar(n);
	for (set<int>::iterator i = vis.begin(); i != vis.end(); i++)
		if (getfar(*i) != tmp) return false;
	return true;
}

int main () {
	int cas = 1;
	while (init()) {
		printf("Case %d is %s\n", cas++, judge()? "a tree." : "not a tree.");
		
	}
	return 0;
}
