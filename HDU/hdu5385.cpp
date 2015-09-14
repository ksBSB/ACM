#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;
const int maxn = 1e5 + 5;

int N, M, D[maxn], R[maxn];
int X[maxn], Y[maxn], W[maxn];
vector<pii> G[maxn];

void init () {
	scanf("%d%d", &N, &M);
	memset(R, 0, sizeof(R));
	for (int i = 1; i <= N; i++) {
		D[i] = -1;
		G[i].clear();
	}

	for (int i = 1; i <= M; i++) {
		W[i] = -1;
		scanf("%d%d", &X[i], &Y[i]);
		G[X[i]].push_back(make_pair(Y[i], i));
		//G[Y[i]].push_back(make_pair(X[i], i));
	}
}

void solve () {
	D[1] = 0;
	queue<int> Q;
	Q.push(1);

	int l = 2, r = N;
	for (int d = 1; d <= N; d++) {
		if (r < l)
			break;
		while (!Q.empty()) {
			int u = Q.front();
			Q.pop();

			for (int i = 0; i < G[u].size(); i++) {
				int v = G[u][i].first;
				if (R[v])
					continue;
				R[v] = G[u][i].second;
			}
		}

		if (R[l]) {
			D[l] = d;
			int u = X[R[l]] + Y[R[l]] - l;
			W[R[l]] = D[l] - D[u];
			Q.push(l++);
		}
		if (r > l && R[r]) {
			D[r] = d;
			int u = X[R[r]] + Y[R[r]] - r;
			W[R[r]] = D[r] - D[u];
			Q.push(r--);
		}
	}

	/*
	for (int i = 1; i <= N; i++)
		printf("%d ", D[i]);
	printf("\n");
	*/
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init ();
		solve ();
		for (int i = 1; i <= M; i++)
			printf("%d\n", W[i] == -1 ? N : W[i]);
	}
	return 0;
}
