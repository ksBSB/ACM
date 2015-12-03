#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 105;
const int inf = 0x3f3f3f3f;

int N, f[maxn][maxn], g[maxn][maxn];

bool dfs(vector<int>& v) {
	if (v.size() == 1) return true;

	int bridge = inf, x = v[0];

	for (int i = 0; i < v.size(); i++) {
		for (int j = i + 1; j  < v.size(); j++)
			bridge = min(bridge, f[v[i]][v[j]]);
	}

	vector<int> l, r;
	for (int i = 0; i < v.size(); i++) {
		if (f[x][v[i]] > bridge) l.push_back(v[i]);
		else r.push_back(v[i]);
	}

	for (int i = 0; i < l.size(); i++) {
		for (int j = 0; j < r.size(); j++)
			if (f[l[i]][r[j]] != bridge) return false;
	}

	if (r.empty()) return false;
	g[l[0]][r[0]] = g[r[0]][l[0]] = bridge;
	return dfs(l) && dfs(r);
}

int main () {
	while (scanf("%d", &N) == 1) {
		vector<int> v;
		v.clear();

		memset(g, 0, sizeof(g));
		for (int i = 1; i <= N; i++) {
			v.push_back(i);
			for (int j = 1; j <= N; j++)
				scanf("%d", &f[i][j]);
			f[i][i] = inf;
		}

		if (dfs(v)) {
			printf("YES\n");
			for (int i = 1; i <= N; i++) {
				g[i][i] = -1;
				for (int j = 1; j <= N; j++)
					printf("%d%c", g[i][j], j == N ? '\n' : ' ');
			}
		} else
			printf("NO\n");
	}
	return 0;
}
