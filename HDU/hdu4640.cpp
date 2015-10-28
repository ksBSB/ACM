#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 16;
const int maxs = (1<<maxn) + 5;
const int inf = 0x3f3f3f3f;
typedef pair<int,int> pii;

int N, M, W[maxs+5][maxn+2], val[maxs+5];
bool used[maxs+5][maxn+2];
vector<pii> G[maxn+5];

struct Node {
	int s, v, w;
	Node (int s = 0, int v = 0, int w = 0): s(s), v(v), w(w) {}
	bool operator < (const Node& u) const { return w > u.w; }
};

void presolve() {
	memset(W, inf, sizeof(W));
	memset(used, 0, sizeof(used));
	W[0][1] = 0;

	priority_queue<Node> que;
	que.push(Node(0, 1, W[0][1]));

	while (!que.empty()) {
		Node cur = que.top();
		que.pop();

		int s = cur.s;
		int u = cur.v;

		if (used[s][u]) continue;
		used[s][u] = true;

		for (int i = 0; i < G[u].size(); i++) {
			int v = G[u][i].first;
			int w = G[u][i].second;
			int vs = s;
			if (v > 1) vs |= (1<<(v-2));

			if (W[vs][v] > W[s][u] + w) {
				W[vs][v] = W[s][u] + w;
				que.push(Node(vs, v, W[vs][v]));
			}
		}
	}
}

void init () {
	scanf("%d%d", &N, &M);
	for (int i = 0; i <= N; i++) G[i].clear();

	int u, v, w;
	for (int i = 0; i < M; i++) {
		scanf("%d%d%d", &u, &v, &w);
		G[u].push_back(make_pair(v, w));
		G[v].push_back(make_pair(u, w));
	}

	presolve();
}

int dp[4][maxs+5];

int solve (int ed) {
	memset(dp, inf , sizeof(dp));
	dp[0][0] = 0;

	int as = (1<<(N-1))-1;
	for (int i = 0; i <= as; i++) {
		val[i] = inf;
		for (int j = 1; j <= N; j++)
			val[i] = min(val[i], W[i][j]);
	}

	for (int i = 0; i < 3; i++) {
		for (int s = 0; s <= as; s++) {
			if (dp[i][s] == inf) continue;
			int vs = as ^ s;
			for (int j = vs; j; j = (j-1)&vs)
				dp[i+1][j|s] = min(dp[i+1][j|s], max(dp[i][s], val[j]));
			dp[i+1][s] = min(dp[i+1][s], dp[i][s]);
		}
	}

	int ret = inf;
	for (int i = 0; i <= as; i++)
		if ((i&ed) == ed) ret =  min(ret, dp[3][i]);
	if (ret == inf) ret = -1;
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();

		int s = 0, n, x;
		scanf("%d", &n);
		while (n--) {
			scanf("%d", &x);
			s |= (1<<(x-2));
		}

		printf("Case %d: %d\n", kcas, solve(s));
	}
	return 0;
}
