#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int maxn = 1e4+5;
const double eps = 1e-6;

struct Edge {
	int u, v;
	Edge (int u = 0, int v = 0) {
		this->u = u;
		this->v = v;
	}
};

int N, M, S, E;
double A[1005][1005];
int f[maxn], idx[maxn];
vector<int> g[maxn];
vector<Edge> G;
queue<int> Q;

inline int getfar(int x) {
	return x == f[x] ? x : f[x] = getfar(f[x]);
}

void bfs (int s, int sign) {
	idx[s] = sign;
	Q.push(s);

	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();

		for (int i = 0; i < g[u].size(); i++) {
			int v = g[u][i];
			if (idx[v] == -1) {
				idx[v] = sign;
				Q.push(v);
			}
		}
	}
}

void init () {
	G.clear();
	for (int i = 0; i <= N; i++) {
		f[i] = i;
		g[i].clear();
	}

	int u, v, r;
	for (int i = 0; i < M; i++) {
		scanf("%d%d%d", &u, &v, &r);
		if (r == 0) {
			g[u].push_back(v);
			g[v].push_back(u);
		} else
			G.push_back(Edge(u, v));
	}

	int n = 0;
	memset(idx, -1, sizeof(idx));
	for (int i = 1; i <= N; i++) {
		if (idx[i] != -1)
			continue;
		bfs(i, n++);
	}
	N = n;
}

double guass (int n, int s, int e) {
	if (s == e)
		return 0;

	for (int i = 0; i < n; i++) {
		int r;
		for (r = i; r < n; r++)
			if (fabs(A[r][i]) > eps)
				break;

		if (r == n)
			continue;

		if (r != i) {
			for (int j = 0; j <= n; j++)
				swap(A[i][j], A[r][j]);
		}

		for (int j = i + 1; j < n; j++) {
			double p = A[j][i] / A[i][i];
			for (int k = 0; k <= n; k++)
				A[j][k] -= A[i][k] * p;
		}
	}

	for (int i = n - 1; i >= 0; i--) {
		for (int j = i + 1; j < n; j++)
			if (fabs(A[j][j]))
				A[i][n] -= A[i][j] * A[j][n] / A[j][j];
	}
	return A[s][n] / A[s][s] - A[e][n] / A[e][e];
}

void solve () {
	memset(A, 0, sizeof(A));
	for (int i = 0; i < G.size(); i++) {
		int u = idx[G[i].u], v = idx[G[i].v];
		int p = getfar(u);
		int q = getfar(v);

		if (p != q)
			f[p] = q;
		A[u][u] += 1;
		A[v][v] += 1;
		A[u][v] -= 1;
		A[v][u] -= 1;
	}
	A[idx[S]][N] = 1;
	A[idx[E]][N] = -1;
	A[N-1][0] = 1;

	if (getfar(idx[S]) != getfar(idx[E])) {
		printf("inf\n");
		return;
	}
	printf("%.6lf\n", guass(N, idx[S], idx[E]));
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d%d%d", &N, &M, &S, &E);
		init();
		solve();
	}
	return 0;
}
