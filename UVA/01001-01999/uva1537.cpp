#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <algorithm>

using namespace std;
const int maxn = 30;
const int inf = 0x3f3f3f3f;

struct Edge {
	int u, v, d;
	Edge(int u = 0, int v = 0, int d = 0): u(u), v(v), d(d) {}
	bool operator < (const Edge& a) const { return d < a.d; }
};

int N, M, K, F[maxn];
map<string,int> ID;
set<int> G[maxn];
vector<Edge> S, E;

int find (int x) { return x == F[x] ? x : F[x] = find(F[x]); }
int getId (char* s) { if (!ID.count(s)) ID[s] = N++; return ID[s]; }

void init () {
	N = 0;
	ID.clear();
	S.clear();
	E.clear();
	scanf("%d", &M);

	ID["Park"] = N++;

	int u, v, d;
	char s1[20], s2[20];
	for (int i = 0; i < M; i++) {
		scanf("%s%s%d", s1, s2, &d);
		int u = getId(s1);
		int v = getId(s2);
		if (u > v) swap(u, v);
		E.push_back(Edge(u, v, d));
	}
	scanf("%d", &K);
}

int dp[maxn], vi[maxn], done[maxn];

void insert(int i) {
	G[E[i].u].insert(i);
	G[E[i].v].insert(i);
}

void erase(int i) {
	G[E[i].u].erase(i);
	G[E[i].v].erase(i);
}

void dfs (int u, int fa, int idx) {
	vi[u] = idx;

	for (set<int>::iterator i = G[u].begin(); i != G[u].end(); i++) {
		int v = E[*i].u + E[*i].v - u, d = E[*i].d;
		if (v == fa) continue;
		dfs(v, u, idx == -1 || E[idx].d < E[*i].d ? *i : idx);
	}
}

int solve () {
	int ret = 0, n = N-1;
	sort(E.begin(), E.end());

	for (int i = 0; i < N; i++) {
		G[i].clear();
		F[i] = i;
	}

	for (int i = 0; i < M; i++) {
		int u = E[i].u, v = E[i].v, d = E[i].d;
		if (u == 0) {
			S.push_back(Edge(i, v, d));
			continue;
		}
		if (find(u) != find(v)) {
			F[find(u)] = find(v);
			insert(i);
			ret += d;
			n--;
		}
	}

	while (n > K);

	memset(dp, inf, sizeof(dp));
	for (int i = 0; i < S.size(); i++) {
		int v = find(S[i].v), d = S[i].d;
		if (d < dp[v]) {
			dp[v] = d;
			vi[v] = i;
		}
	}

	memset(done, 0, sizeof(done));
	for (int i = 0; i < N; i++) if (dp[i] != inf) {
		done[vi[i]] = 1;
		int idx = S[vi[i]].u;
		ret += E[idx].d;
		insert(idx);
	}

	memset(dp, inf, sizeof(dp));
	dp[n] = ret;
	for (int k = n+1; k <= K; k++) {
		memset(vi, -1, sizeof(vi));
		dfs(0, -1, -1);

		/*
		for (int i = 0; i < N; i++)
			printf("%d ", vi[i]);
		printf("\n");

		for (int i = 0; i < N; i++) {
			for (set<int>::iterator j = G[i].begin(); j != G[i].end(); j++)
				printf("(%d,%d %d) ", *j, E[*j].v, E[*j].d);
			printf("\n");
			}
			printf("\n");
			*/

		int add = inf, rec = -1;
		for (int i = 0; i < S.size(); i++) {
			if (done[i]) continue;
			int v = S[i].v;
			int tmp = E[vi[v]].d;

			if (S[i].d - tmp < add) {
				add = S[i].d - tmp;
				rec = i;
			}
		}

		dp[k] = dp[k-1] + add;
		erase(vi[S[rec].v]);
		insert(S[rec].u);
		done[rec] = 1;
	}

	int ans = inf;
	for (int i = n; i <= K; i++)
		ans = min(ans, dp[i]);

	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("Total miles driven: %d\n", solve());
		if (cas) printf("\n");
	}
	return 0;
}
