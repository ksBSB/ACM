#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 1005;
const int inf = 0x3f3f3f3f;

int N, Q, D[maxn];
vector<int> g[maxn];
map<string, int> idx;
queue<int> que;

int bfs(int s) {
	memset(D, inf, sizeof(D));
	int ret = D[s] = 0;
	que.push(s);

	while (!que.empty()) {
		int u = que.front();
		que.pop();

		for (int i = 0; i < g[u].size(); i++) {
			int v = g[u][i];
			if (D[v] > D[u] + 1) {
				D[v] = D[u] + 1;
				que.push(v);
			}
		}
	}
	for (int i = 1; i <= N; i++)
		ret = max(ret, D[i]);
	return ret;
}

int main () {
	while (scanf("%d", &N) == 1 && N) {
		idx.clear();
		string name, a, b;

		for (int i = 1; i <= N; i++) {
			g[i].clear();
			cin >> name;
			idx[name] = i;
		}

		scanf("%d", &Q);
		for (int i = 0; i < Q; i++) {
			cin >> a >> b;
			g[idx[a]].push_back(idx[b]);
			g[idx[b]].push_back(idx[a]);
		}

		int ans = 0;
		for (int i = 1; i <= N; i++)
			ans = max(ans, bfs(i));
		printf("%d\n", ans == inf ? -1 : ans);
	}
	return 0;
}
