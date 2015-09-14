#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;
const int maxn = 400;
const int maxm = maxn * maxn >> 1;
const int inf = 0x3f3f3f3f;

struct Edge {
	int u, v, d, idx;
	Edge(int u = 0, int v = 0, int d = 0, int idx = 0): u(u), v(v), d(d), idx(idx) {}
	bool operator < (const Edge& a) const { return idx < a.idx; }
}E[maxm];

int N, M, F[maxn], vi[maxm];
set<Edge> S;
set<pii> G[maxn];

typedef set<Edge>::iterator iter;

bool cmp(const Edge& a, const Edge& b) { return a.d < b.d; }
int find(int x) { return x == F[x] ? x : F[x] = find(F[x]); }

void addEdge (int i) {
	S.insert(E[i]);
	G[E[i].u].insert(make_pair(E[i].v, i));
	G[E[i].v].insert(make_pair(E[i].u, i));
}

void eraseEdge(int i) {
	S.erase(E[i]);
	G[E[i].u].erase(make_pair(E[i].v, i));
	G[E[i].v].erase(make_pair(E[i].u, i));
}

int C;
Edge temp[maxn];

bool dfs (int u, int fa, int e) {
	if (u == e) return true;
	for (set<pii>::iterator i = G[u].begin(); i != G[u].end(); i++) {
		int v = i->first;
		if (v == fa) continue;

		temp[C++] = E[i->second];
		if (dfs(v, u, e)) return true;
		C--;
	}
	return false;
}

int findMinEdge(int u, int v) {
	C = 0;
	dfs(u, -1, v);
	sort(temp, temp + C, cmp);
	return temp[0].idx;
}

int solve () {
	S.clear();
	for (int i = 0; i < N; i++)
		F[i] = i, G[i].clear();
	memset(vi, 0, sizeof(vi));

	int n = N, l = inf, ans;
	for (int i = 0; i < M; i++) E[i].idx = i;

	for (int i = 0; i < M; i++) {
		int u = E[i].u, v = E[i].v, d = E[i].d;
		if (find(u) != find(v)) {
			n--;
			vi[i] = 1;
			l = min(l, d);
			F[find(u)] = find(v);
			addEdge(i);

			if (n == 1) {
				ans = d - l;
				break;
			}
		}
	}

	for (int i = 0; i < M; i++) if (!vi[i]) {
		int u = E[i].u, v = E[i].v, d = E[i].d;

		int t = findMinEdge(u, v);
		if (E[t].d >= d) continue;

		eraseEdge(t);
		addEdge(i);

		int l = inf, r = 0;
		for (iter it = S.begin(); it != S.end(); it++) {
			l = min(l, it->d);
			r = max(r, it->d);
		}
		ans = min(ans, r - l);
	}
	return ans;
}

int main () {
	while (scanf("%d", &N) == 1 && N) {
		scanf("%d", &M);
		for (int i = 0; i < M; i++)
			scanf("%d%d%d", &E[i].u, &E[i].v, &E[i].d);
		sort(E, E + M, cmp);
		printf("%d\n", solve());
	}
	return 0;
}
