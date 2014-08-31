#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 1005;

int N, K, x;
int pos[5][maxn];
vector<int> g[maxn];

bool check (int a, int b) {
	for (int i = 0; i < K; i++)
		if (pos[i][a] >= pos[i][b])
			return false;
	return true;
}

int bfs (int s) {
	int d[maxn];
	memset(d, 0, sizeof(d));

	queue<int> que;
	que.push(s);

	int ans = 0;
	while (!que.empty() ) {
		int u = que.front();
		ans = max(ans, d[u]);
		que.pop();

		for (int i = 0; i < g[u].size(); i++) {
			int v = g[u][i];
			if (d[u] + 1 > d[v]) {
				d[v] = d[u] + 1;
				que.push(v);
			}
		}
	}
	return ans;
}

int main () {
	scanf("%d%d", &N, &K);
	for (int i = 0; i < K; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &x);
			pos[i][x] = j;
		}
	}

	for (int i = 1; i <= N; i++) {
		g[0].push_back(i);
		for (int j = 1; j <= N; j++)
			if (check(i, j))
				g[i].push_back(j);
	}

	printf("%d\n", bfs(0));
	return 0;
}
