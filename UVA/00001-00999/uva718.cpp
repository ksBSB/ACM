#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 105;
const int INF = 0x3f3f3f3f;
int F, E, A, B, X[maxn], Y[maxn];
vector<int> g[maxn];

void gcd (int a, int b, int& d, int& x, int& y) {
	if (b == 0) {
		d = a;
		x = 1;
		y = 0;
	} else {
		gcd(b, a%b, d, y, x);
		y -= (a/b)*x;
	}
}

void addPoint (int k, int u, int v) {
	if (k < Y[v])
		return ;
	if ((k-Y[v]) % X[v] == 0) {
		g[v].push_back(u);
		g[u].push_back(v);
	}
}

void addEdge (int u, int v) {
	int a = X[u], b = -X[v], c = Y[v] - Y[u];
	int d, xi, yi;
	gcd(a, b, d, xi, yi);

	if (c % d)
		return ;

	int lower = -INF, up = INF;

	double T = (F - Y[u]) * 1.0 / X[u];
	if (b / d > 0) {
		up = min (up, (int)floor((T*d - xi*c) / b));
		lower = max(lower, (int)ceil(-xi*c*1.0/b));
	} else {
		up = min(up, (int)floor(-xi*c*1.0/b));
		lower = max(lower, (int)ceil((T*d - xi*c) / b));
	}

	T = (F - Y[v]) * 1.0 / X[v];
	if (a / d > 0) {
		up = min(up, (int)floor((yi*c*1.0)/a));
		lower = max(lower, (int)ceil((T*d*-yi*c) / a));
	} else {
		up = min(up, (int)floor((T*d*-yi*c) / a));
		lower = max(lower, (int)ceil((yi*c*1.0)/a));
	}

	if (up < lower)
		return;
	g[u].push_back(v);
	g[v].push_back(u);
}

void init () {
	scanf("%d%d%d%d", &F, &E, &A, &B);
	for (int i = 0; i <= E+1; i++)
		g[i].clear();

	for (int i = 1; i <= E; i++) {
		scanf("%d%d", &X[i], &Y[i]);
		addPoint(A, 0, i);
		addPoint(B, E+1, i);
	}

	for (int i = 1; i <= E; i++) {
		for (int j = 1; j <= E; j++)
			addEdge(i, j);
	}
}

bool bfs (int s, int e) {
	int vis[maxn];
	memset(vis, 0, sizeof(vis));

	queue<int> que;
	que.push(s);
	vis[s] = 1;

	while (!que.empty()) {
		int u = que.front();
		que.pop();

		if (u == e)
			return true;

		for (int i = 0; i < g[u].size(); i++) {
			int v = g[u][i];

			if (vis[v])
				continue;

			que.push(v);
			vis[v] = 1;
		}
	}
	return false;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init ();
		if (bfs(0, E+1))
			printf("It is possible to move the furniture.\n");
		else
			printf("The furniture cannot be moved.\n");
	}
	return 0;
}
