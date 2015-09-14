#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 105;

int N, M, S, W[maxn][maxn], V[maxn];
vector<int> G[maxn];

bool judge (int u, int v) {
	int c = 0;
	for (int i = 1; i <= M; i++)
		if (W[i][u] < W[i][v])
			c++;
	return 2 * c > M;
}

void init () {
	int x;
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &x);
			W[i][x] = j;
		}
	}

	for (int i = 1; i <= N; i++)
		G[i].clear();
	for (int i = 1; i <= N; i++) {
		for (int j = i + 1; j <= N; j++) {
			if (judge(i, j)) G[i].push_back(j);
			else if (judge(j, i)) G[j].push_back(i);
		}
	}
}

bool solve () {
	queue<int> Q;
	memset(V, 0, sizeof(V));
	Q.push(S);
	int cnt = V[S] = 1;

	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		for (int i = 0; i < G[u].size(); i++) {
			int v = G[u][i];
			if (V[v]) continue;
			V[v] = 1;
			cnt++;
			Q.push(v);
		}
	}
	return cnt == N;
}

int main () {
	while (scanf("%d%d%d", &N, &M, &S) == 3 && N + M + S) {
		init ();
		printf("%s\n", solve() ? "yes" : "no");
	}
	return 0;
}
