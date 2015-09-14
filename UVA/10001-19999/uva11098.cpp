#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 305;
const ll inf = 0x3f3f3f3f3f3f3f3f;

int N, X[maxn], Y[maxn], R[maxn], E[maxn];
int cntlock, cntscc, sccno[maxn], pre[maxn];
vector<int> G[maxn], T[maxn];
stack<int> S;

struct State {
	int pre, idx;
	ll val;
	State(int pre = 0, int idx = 0, ll val = 0): pre(pre), idx(idx), val(val) {}
};

inline bool cmpVal(const State& a, const State& b) { return a.val < b.val; }
inline bool cmpIdx(const State& a, const State& b) { return a.pre < b.pre; }

int dfs (int u) {
	int lowu = pre[u] = ++cntlock;
	S.push(u);

	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (!pre[v]) {
			int lowv = dfs(v);
			lowu = min(lowu, lowv);
		} else if (!sccno[v])
			lowu = min(lowu, pre[v]);
	}

	if (lowu == pre[u]) {
		cntscc++;
		while (true) {
			int x = S.top(); S.pop();
			sccno[x] = cntscc;
			if (x == u) break;
		}
	}
	return lowu;
}

void findSCC() {
	cntlock = cntscc = 0;
	memset(pre, 0, sizeof(pre));
	memset(sccno, 0, sizeof(sccno));
	for (int i = 0; i < N; i++)
		if (!pre[i]) dfs(i);
}

inline ll distance(ll a, ll b) { return a * a + b * b; }

bool judge (int a, int b) {
	ll c = distance((ll)X[a]-X[b], (ll)Y[a]-Y[b]);
	ll d = (R[a] + R[b] + E[a]); d = d * d;
	return d >= c;
}

void init () {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d%d%d%d", &X[i], &Y[i], &R[i], &E[i]);

	for (int i = 0; i < N; i++) {
		G[i].clear();
		for (int j = 0; j < N; j++) if (i != j)
			if (judge(i, j)) G[i].push_back(j);
	}
	findSCC();
}

void solve () {
	ll C[maxn], sum = 0;
	int in[maxn], rec[maxn];
	memset(in, 0, sizeof(in));
	for (int i = 1; i <= cntscc; i++)
		C[i] = inf, T[i].clear();

	for (int i = 0; i < N; i++) {
		int u = sccno[i];
		if (C[u] > E[i]) {
			C[u] = E[i];
			rec[u] = i;
		}

		for (int j = 0; j < G[i].size(); j++) {
			int v = sccno[G[i][j]];
			if (u != v) {
				T[v].push_back(u);
				in[u]++;
			}
		}
	}


	int p = 0, c = 0;
	queue<int> que;
	vector<State> ans, tmp;
	for (int i = 1; i <= cntscc; i++) if (!in[i]) que.push(i);
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		pre[u] = cntlock++;
		if (T[u].size() == 0) {
			ans.push_back(State(p++, rec[u], C[u]));
			sum += C[u], c++;
		} else
			tmp.push_back(State(p++, rec[u], C[u]));

		for (int i = 0; i < T[u].size(); i++) {
			int v = T[u][i];
			in[v]--;
			if (in[v] == 0) que.push(v);
		}
	}

	sort(tmp.begin(), tmp.end(), cmpVal);
	p = 0;
	while (p < tmp.size()) {
		if (tmp[p].val * c >= sum) break;
		ans.push_back(tmp[p]);
		sum += tmp[p].val;
		c++, p++;
	}

	sort(ans.begin(), ans.end(), cmpIdx);
	for (int i = 0; i < ans.size(); i++)
		printf(" %d", ans[i].idx);
	printf("\n");
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();
		printf("Case #%d:", kcas);
		solve();
	}
	return 0;
}
