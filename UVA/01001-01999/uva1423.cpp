#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 105;

int N, A[maxn], C[maxn];
char S[maxn];
vector<int> G[maxn];

void addEdge(int u, int v) {
	C[v]++;
	G[u].push_back(v);
}

void solve () {
	int d = 0;
	queue<int> Q;
	for (int i = 0; i <= N; i++)
		if (C[i] == 0) Q.push(i);

	while (!Q.empty()) {
		int sz = Q.size();
		for (int k = 0; k < sz; k++) {
			int u = Q.front();
			Q.pop();
			A[u] = d;
			for (int i = 0; i < G[u].size(); i++) {
				int v = G[u][i];
				C[v]--;
				if (C[v] == 0)
					Q.push(v);
			}
		}
		d++;
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%s", &N, S);
		memset(C, 0, sizeof(C));
		for (int i = 0; i <= N; i++) G[i].clear();

		int p = 0;
		for (int j = 0; j <= N; j++) {
			for (int i = j + 1; i <= N; i++) {
				if (S[p] == '+')
					addEdge(j, i);
				else if (S[p] == '-')
					addEdge(i, j);
				p++;
			}
		}

		solve();
		for (int i = 1; i <= N; i++) {
			printf("%d%c", A[i]-A[i-1], i == N ? '\n' : ' ');
		}
	}
	return 0;
}
