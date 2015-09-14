#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 1005;
const int maxm = 25005;

struct Edge {
	int u, v, d;
	Edge(int u = 0, int v = 0, int d = 0): u(u), v(v), d(d) {}
	bool operator < (const Edge& a) const { return d < a.d; }
}E[maxm];

int N, M, F[maxn];

int find (int x) { return x == F[x] ? x : F[x] = find(F[x]); }

void init () {
	for (int i = 0; i < N; i++) F[i] = i;

	for (int i = 0; i < M; i++)
		scanf("%d%d%d", &E[i].u, &E[i].v, &E[i].d);
	sort(E, E + M);
}

int main () {
	vector<int> ans;
	while (scanf("%d%d", &N, &M) == 2 && N + M) {
		init();

		ans.clear();
		for (int i = 0; i < M; i++) {
			int u = E[i].u, v = E[i].v;
			if (find(u) != find(v))
				F[find(u)] = find(v);
			else
				ans.push_back(E[i].d);
		}

		if (ans.size()) {
			for (int i = 0; i < ans.size(); i++)
				printf("%d%c", ans[i], i == ans.size()-1 ? '\n' : ' ');
		} else
			printf("forest\n");
	}
	return 0;
}
