#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const int maxn = 1e5 + 5;

int N, T[maxn], L[maxn], R[maxn];
int cntlock, cntbcc, pre[maxn], low[maxn], bccno[maxn], iscut[maxn];
vector<int> G[maxn], BCC[maxn];
stack<pii> S;

int dfs (int u, int fa) {
	int lowu = pre[u] = ++cntlock, child = 0;

	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		pii e = make_pair(u, v);

		if (!pre[v]) {
			child++;
			S.push(e);
			int lowv = dfs(v, u);
			lowu = min(lowu, lowv);

			if (lowv >= pre[u]) {
				iscut[u] = 1;
				BCC[++cntbcc].clear();

				while (true) {
					e = S.top(); S.pop();
					if (bccno[e.first] != cntbcc) {
						BCC[cntbcc].push_back(e.first);
						bccno[e.first] = cntbcc;
					}
					if (bccno[e.second] != cntbcc) {
						BCC[cntbcc].push_back(e.second);
						bccno[e.second] = cntbcc;
					}

					if (u == e.first && v == e.second) break;
				}
			}
		} else if (v != fa && pre[v] < pre[u]) {
			S.push(e);
			lowu = min(lowu, pre[v]);
		}
	}

	if (fa < 0 && child == 1) iscut[u] = 0;
	return low[u] = lowu;
}

void findBCC () {
	cntlock = cntbcc = 0;
	memset(pre, 0, sizeof(pre));
	memset(iscut, 0, sizeof(iscut));
	memset(bccno, 0, sizeof(bccno));
	dfs(0, -1);
}

void init () {
	int n = 0;
	for (int i = 1; i <= N; i++) {
		scanf("%d%d", &L[i], &R[i]);
		T[n++] = L[i];
		T[n++] = R[i];
	}

	sort(T, T + n);
	n = unique(T, T + n) - T;

	for (int i = 0; i < n; i++) G[i].clear();

	for (int i = 1; i <= N; i++) {
		int u = lower_bound(T, T + n, L[i]) - T;
		int v = lower_bound(T, T + n, R[i]) - T;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	N = n;
	findBCC();
}

int main () {
	int cas = 1;
	while (scanf("%d", &N) == 1 && N) {
		init ();
		ll ans1 = 0, ans2 = 1;

		if (cntbcc == 1) {
			ans1 = 2, ans2 = 1LL * N * (N-1) / 2;
		} else {
			for (int i = 1; i <= cntbcc; i++) {
				int c = 0;
				for (int j = 0; j < BCC[i].size(); j++)
					if (iscut[BCC[i][j]]) c++;
				if (c == 1) {
					ans1++;
					ans2 *= BCC[i].size() - c;
				}
			}
		}
		printf("Case %d: %lld %lld\n", cas++, ans1, ans2);
	}
	return 0;
}
