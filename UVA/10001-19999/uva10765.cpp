#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
const int maxn = 10005;

struct State {
	int u, v;
	State(int u = 0, int v = 0): u(u), v(v) {}
	bool operator < (const State& a) const { return v > a.v || (v == a.v && u < a.u); }
};

int N, M, K, F[maxn];
int cntbcc, cntlock, pre[maxn], iscut[maxn], bccno[maxn];
vector<int> G[maxn], BCC[maxn];
stack<State> S;
vector<State> ans;

int find (int x) { return x == F[x] ? x : F[x] = find(F[x]); }

void init () {
	for (int i = 0; i < N; i++) G[i].clear();
	K = N;
	for (int i = 0; i < N; i++) F[i] = i;
	
	int u, v;
	while (scanf("%d%d", &u, &v) == 2) {
		if (u == -1 && v == -1) break;
		if (find(u) != find(v)) {
			K--;
			F[find(u)] = find(v);
		}
		G[u].push_back(v);
		G[v].push_back(u);
	}
}

int dfs(int u, int fa) {
	int lowu = pre[u] = ++cntlock, child = 0;

	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		State e = State(u, v);
		if (!pre[v]) {
			S.push(e);
			child++;
			int lowv = dfs(v, u);
			lowu = min(lowu, lowv);
			if (lowv >= pre[u]) {
				iscut[u] = 1;
				BCC[++cntbcc].clear();
				while (true) {
					State x = S.top(); S.pop();
					if (bccno[x.u] != cntbcc) {
						BCC[cntbcc].push_back(x.u);
						bccno[x.u] = cntbcc;
					}

					if (bccno[x.v] != cntbcc) {
						BCC[cntbcc].push_back(x.v);
						bccno[x.v] = cntbcc;
					}
					if (u == x.u && v == x.v) break;
				}
			} 
		} else if (pre[v] < pre[u] && v != fa) {
			S.push(e);
			lowu = min(lowu, pre[v]);
		}
	}
	if (fa < 0 && child == 1) iscut[u] = 0;
	return lowu;
}

void findBCC () {
	cntlock = cntbcc = 0;
	memset(pre, 0, sizeof(pre));
	memset(iscut, 0, sizeof(iscut));
	memset(bccno, 0, sizeof(bccno));
	for (int i = 0; i < N; i++)
		if (!pre[i]) dfs(i, -1);
}

void solve () {
	ans.clear();
	vector<int> T;

	for (int i = 0; i < N; i++) {
		T.clear();
		if (!iscut[i]) {
			ans.push_back(State(i, K));
			continue;
		}

		//int c = 0;
		for (int j = 0; j < G[i].size(); j++) {
			int v = G[i][j];
		//	if (iscut[v]) c++;
			//else 
				T.push_back(bccno[v]);
		}
		sort(T.begin(), T.end());
		int n = unique(T.begin(), T.end()) - T.begin();
		ans.push_back(State(i, n));
	}

	sort(ans.begin(), ans.end());
	for (int i = 0; i < M; i++)
		printf("%d %d\n", ans[i].u, ans[i].v);
	printf("\n");
}

int main () {
	while (scanf("%d%d", &N, &M) == 2 && N + M) {
		init();
		findBCC();
		solve();
	}
	return 0;
}
