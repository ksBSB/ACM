#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 1005;
const int maxm = 30;

vector<int> G[maxm];
int N, top, F[maxm], in[maxm], ot[maxm], vis[maxn], path[maxn];

struct Edge {
	char s[maxn];
	int u, v;
	void touch() {
		u = s[0] - 'a';
		v = s[strlen(s)-1] - 'a';
	}
}E[maxn];

int find(int x) { return x == F[x] ? x : F[x] = find(F[x]); }
void addEdge(int u, int v) { ot[u]++, in[v]++; }
bool cmp(const Edge& a, const Edge& b) { return strcmp(a.s, b.s) < 0; }

void init () {
	top = 0;
	scanf("%d", &N);
	for (int i = 0; i < maxm; i++) G[i].clear();
	memset(in, 0, sizeof(in));
	memset(ot, 0, sizeof(ot));
	memset(vis, 0, sizeof(vis));

	for (int i = 1; i <= N; i++) {
		scanf("%s", E[i].s);
		E[i].touch();
		addEdge(E[i].u, E[i].v);
	}
	sort(E + 1, E + N + 1, cmp);
	for (int i = 1; i <= N; i++)
		G[E[i].u].push_back(i);
}

void dfs (int u) {
	for (int i = 0; i < G[u].size(); i++) {
		int e = G[u][i];
		if (vis[e]) continue;
		vis[e] = 1;
		dfs(E[e].v);
		path[top++] = e;
	}
}

bool judge (int& r) {
	int a = 0, b = 0;
	for (int i = 0; i < maxm; i++) {
		if (ot[i] == in[i] + 1)
			a++, r=i;
		else if (ot[i] == in[i] - 1)
			b++;
		else if (ot[i] != in[i])
			return false;
	}

	if (a > 1 || b > 1 || a + b == 1) return false;
	if (a + b == 0) {
		for (int i = 0; i < maxm; i++)
			if (in[i]) { r = i; break; }
	}

	int c = 0;
	for (int i = 0; i < maxm; i++) {
		F[i] = i;
		if (in[i] + ot[i]) c++;
	}

	for (int i = 1; i <= N; i++) {
		if (find(E[i].u) != find(E[i].v)) {
			F[find(E[i].u)] = find(E[i].v);
			c--;
		}
	}
	return c == 1;
}

int main () {
	int cas, r;
	scanf("%d", &cas);
	while (cas--) {
		init();

		if (judge(r)) {
			dfs(r);
			for (int i = top-1; i >= 0; i--)
				printf("%s%c", E[path[i]].s, i == 0 ? '\n' : '.');
		} else printf("***\n");
	}
	return 0;
}
