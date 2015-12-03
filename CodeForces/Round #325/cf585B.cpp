#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 105;
const int dir[3] = {-1, 0, 1};
typedef pair<int,int> pii;

int N, K, vis[maxn][3];
char G[3][maxn];

bool judge () {
	queue<pii> que;
	memset(vis, 0, sizeof(vis));

	for (int i = 0; i < 3; i++) if (G[i][0] == 's') {
		que.push(make_pair(0, i));
		vis[0][i] = 1;
	}

	while (!que.empty()) {
		pii cur = que.front();
		que.pop();
		int u = cur.first * 3;
		int h = cur.second;
		//printf("%d %d\n", u, h);

		if (u + 1 >= N) return true;
		if (G[h][u+1] != '.') continue;

		for (int i = 0; i < 3; i++) {
			int vh = h + dir[i], vv = u+1;

			if (vh < 0 || vh >= 3) continue;

			bool flag = true;
			for (int j = 0; j <= 2 && flag; j++) {
				if (vv + j >= N) return true;
				if (G[vh][vv+j] != '.') flag = false;
			}

			if (flag) {
				int t = (vv + 2) / 3;
				if (!vis[t][vh]) {
					que.push(make_pair(t, vh));
					vis[t][vh] = 1;
				}
			}
		}
	}
	return false;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d", &N, &K);
		for (int i = 0; i < 3; i++)
			scanf("%s", G[i]);
		printf("%s\n", judge() ? "YES" : "NO");
	}
	return 0;
}
