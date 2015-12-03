#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 1005;
const int inf = 0x3f3f3f3f;
const int dir[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
typedef pair<int,int> pii;

int N, M, V[4][maxn][maxn], K = 0;
char G[maxn][maxn];

void bfs(int s, int d[maxn][maxn]) {
	queue<pii> que;

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++) if (G[i][j] == '0' + s) {
			d[i][j] = 0;
			que.push(make_pair(i, j));
		}

	if (!que.empty()) K++;

	while (!que.empty()) {
		int x = que.front().first;
		int y = que.front().second;
		que.pop();

		for (int i = 0; i < 4; i++) {
			int p = x + dir[i][0];
			int q = y + dir[i][1];

			if (p <= 0 || p > N || q <= 0 || q > M) continue;
			if (G[p][q] == '#') continue;
			if (d[p][q] > d[x][y] + 1) {
				d[p][q] = d[x][y] + 1;
				que.push(make_pair(p, q));
			}
		}
	}
}

int solve () {
	if (K <= 1) return 0;

	vector<int> tmp;
	tmp.clear();

	for (int x = 1; x <= K; x++) {
		for (int y = x + 1; y <= K; y++) {
			int ret = inf;
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= M; j++) {
					if (G[i][j] == '0' + y)
						ret = min(ret, V[x][i][j]);
				}
			}
			tmp.push_back(ret);
		}
	}
	sort(tmp.begin(), tmp.end());
	if (tmp[0] == inf) return inf;
	if (K == 2) return tmp[0] - 1;

	if (tmp[1] == inf) return inf;
	return tmp[0] + tmp[1] - 2;
}

int main () {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++)
		scanf("%s", G[i] + 1);
	memset(V, inf, sizeof(V));

	for (int i = 1; i <= 3; i++)
		bfs(i, V[i]);
	int ans = solve();

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (G[i][j] != '.') continue;

			int tmp = 0;
			for (int k = 1; k <= K; k++) {
				if (V[k][i][j] == inf) {
					tmp = inf;
					break;
				}
				tmp += V[k][i][j];
			}
			if (tmp == inf) continue;
			ans = min(ans, tmp-K+1);
		}
	}

	if (ans == inf) ans = -1;
	printf("%d\n", ans);
	return 0;
}
