#include <cstdio>
#include <cstring>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;
const int maxn = 50;

int N, M, W, cnt, ans[maxn], pos[maxn], C[maxn], arr[maxn][maxn], vis[205];
vector<pii> G;

void init () {
	G.clear();
	scanf("%d%d%d", &N, &M, &W);

	for (int i = 0; i < N; i++) {
		int c, t, s = 0, x;
		scanf("%d%d", &C[i], &t);
		for (int j = 0; j < C[i]; j++)
			scanf("%d", &arr[i][j]);
		G.push_back(make_pair(t, i));
	}
	sort(G.begin(), G.end());
}

int draw (int t, int v) {
	int ret = 0;
	for (int i = 0; i < C[t]; i++) {
		if (vis[arr[t][i]] == 0) ret++;
		vis[arr[t][i]] += v;
	}
	return ret;
}

void dfs (int d, int n) {

	if (n + d < cnt) return;

	if (d > cnt) {
		cnt = d;
		memcpy(ans, pos, sizeof(int) * cnt);
	}

	for (int i = (d == 0 ? 0 : pos[d-1] + 1); i < N; i++) {
		if (d && G[i].first - G[pos[d-1]].first > W) break;
		int t = draw(G[i].second, 1);
		if (t >= 3) {
			pos[d] = i;
			dfs(d + 1, N - i - 1);
		}
		draw(G[i].second, -1);
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		cnt = 0;
		memset(vis, 0, sizeof(vis));
		dfs(0, N-1);
		for (int i = 0; i < cnt; i++)
			ans[i] = G[ans[i]].second + 1;
		sort(ans, ans + cnt);

		printf("%d\n", cnt);
		for (int i = 0; i < cnt; i++)
			printf("%d%c", ans[i], i == cnt-1 ? '\n' : ' ');
	}
	return 0;
}
