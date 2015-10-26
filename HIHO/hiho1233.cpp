#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 10;
const int maxs = 1e6;
const int dir[2] = {1, -1};
const int inf = 0x3f3f3f3f;
typedef pair<int,int> pii;

int N, E, V[maxn], P[maxn], T[maxn], vis[8][maxs];

int idx(int* c) {
	int ret = 0;
	for (int i = 0; i < N; i++)
		ret = ret * N + c[i];
	return ret;
}

void ridx(int* c, int s) {
	for (int i = N-1; i >= 0; i--) {
		c[i] = s % N;
		s /= N;
	}
}

bool judge (int w, int u, int p) {
	if (p < 0 || p >= N) return false;
	return w < T[p] && w == T[u];
}

void bfs (int n, int* v) {
	N = n;
	for (int i = 0; i < N; i++) V[i] = T[i] = i;
	int s = idx(T);
	v[s] = 0;

	queue<pii> Q;
	Q.push(make_pair(s, 0));

	while (!Q.empty()) {
		int u = Q.front().first;
		int c = Q.front().second;
		Q.pop();

		ridx(P, u);
		for (int i = 0; i < N; i++) T[i] = inf;
		for (int i = 0; i < N; i++) T[P[i]] = min(T[P[i]], V[i]);

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < 2; j++) {
				if (judge(V[i], P[i], P[i]+dir[j])) {
					P[i] += dir[j];
					int e = idx(P);
					if (v[e] == -1) {
						Q.push(make_pair(e, c+1));
						v[e] = c+1;
					}
					P[i] -= dir[j];
				}
			}
		}
	}
}

void init () {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) scanf("%d", &V[i]);
	memcpy(P, V, sizeof(V));

	sort(P, P + N);
	for (int i = 0; i < N; i++) T[i] = lower_bound(P, P + N, V[i]) - P;
	for (int i = 0; i < N; i++) P[T[i]] = i;
	//for (int i = 0; i < N; i++) printf("%d ", P[i]);
	//printf("\n");
	E = idx(P);
}

int main () {
	int cas;
	scanf("%d", &cas);
	memset(vis, -1, sizeof(vis));
	for (int i = 1; i < 8; i++) bfs(i, vis[i]);
	while (cas--) {
		init();
		printf("%d\n", vis[N][E]);
	}
	return 0;
}
