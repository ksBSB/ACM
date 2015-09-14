#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;
const int maxn = 105;
const int inf = 0x3f3f3f3f;

bool done[maxn][maxn];
int N, M, D[maxn][maxn];
vector<pii> G[maxn];
map<string, int> T;

void init () {
	int d;
	char city1[maxn], city2[maxn];
	T.clear();

	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		G[i].clear();
		scanf("%s", city1);
		T[city1] = i;
	}

	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		scanf("%s%s%d", city1, city2, &d);
		int u = T[city1], v = T[city2];
		G[u].push_back(make_pair(v, d));
	}
}

/*
bool SPFA (int s, int e) {
	for (int i = 0; i <= N; i++)
		for (int j = 0; j <= 101; j++) D[i][j] = inf;
	memset(inque, 0, sizeof(inque));
	memset(otque, 0, sizeof(otque));
	D[s][0] = 0;

	queue<pii> Q;
	Q.push(make_pair(s, 0));
	while (!Q.empty()) {
		int u = Q.front().first;
		int t = Q.front().second;
		Q.pop();

		inque[u][t] = 0;
		otque[u][t]++;
		if (otque[u][t] > N) return false;
		for (int i = 0; i < G[u].size(); i++) {
			int v = G[u][i].first, w = G[u][i].second;
			if (D[v][t+1] > D[u][t] + w)
				D[v][t+1] = D[u][t] + w;

			if (t <= 100 && !inque[v][t+1]) {
				inque[v][t+1] = 1;
				Q.push(make_pair(v, t + 1));
			}
		}
	}
	return true;
}
*/

struct State {
	int u, t, d;
	State(int u = 0, int t = 0, int d = 0): u(u), t(t), d(d) {}
	bool operator < (const State& a) const { return d > a.d; }
};

void Dijkstra(int s) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j <= 100; j++) D[i][j] = inf;
	D[s][0] = 0;
	memset(done, 0, sizeof(done));

	priority_queue<State> Q;
	Q.push(State(s, 0, D[s][0]));

	while (!Q.empty()) {
		int u = Q.top().u;
		int t = Q.top().t;
		Q.pop();

		if (done[u][t]) continue;
		done[u][t] = true;

		for (int i = 0; i < G[u].size(); i++) {
			int v = G[u][i].first, w = G[u][i].second;
			if (D[v][t+1] > D[u][t] + w) {
				D[v][t+1] = D[u][t] + w;
				Q.push(State(v, t+1, D[v][t+1]));
			}
		}
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		if (kcas != 1) printf("\n");
		init();
		Dijkstra(0);

		printf("Scenario #%d\n", kcas);
		int q, x;
		scanf("%d", &q);
		while (q--) {
			scanf("%d", &x);
			int ans = inf;
			x = min(x+1, N-1);
			for (int i = 0; i <= x; i++)
				ans = min(ans, D[N-1][i]);
			if (ans != inf)
				printf("Total cost of flight(s) is $%d\n", ans);
			else
				printf("No satisfactory flights\n");
		}
	}
	return 0;
}
