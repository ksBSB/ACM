#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 105;

int N, M, G[maxn][maxn];
int V[5 * maxn], H[maxn][maxn], L[maxn][maxn];

void init () {
	scanf("%d%d", &N, &M);
	for (int k = 0; k < 2; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++)
				scanf("%d", &G[i][j]);
		}
	}

	memset(V, 0, sizeof(V));
	memset(H, 0, sizeof(H));
	memset(L, 0, sizeof(L));
	int x, y;
	char order[5];
	for (int i = 1; i <= M; i++) {
		scanf("%s%d%d", order, &x, &y);
		if (order[0] == 'H')
			H[x][y] = i;
		else
			L[x][y] = i;
	}
}

int hv[maxn], lv[maxn], ans[maxn * 5];

void solve () {
	int mv = M;
	memset(hv, 0, sizeof(hv));
	memset(lv, 0, sizeof(lv));

	while (mv) {
		bool flag = true;
		for (int i = 1; i <= N; i++) {
			if (hv[i])
				continue;
			int t = -1, c = 0;
			for (int j = 1; j <= N; j++) {
				if (G[i][j] == 0)
					continue;
				if (G[i][j] != t)
					c++;
				t = G[i][j];
			}

			if (c == 1 && H[i][t]) {
				for (int j = 1; j <= N; j++)
					G[i][j] = 0;
				ans[mv--] = H[i][t];
				hv[i] = V[H[i][t]] = 1;
				flag = false;
			}
		}

		for (int i = 1; i <= N; i++) {
			if (lv[i])
				continue;
			int t = -1, c = 0;
			for (int j = 1; j <= N; j++) {
				if (G[j][i] == 0)
					continue;
				if (G[j][i] != t)
					c++;
				t = G[j][i];
			}

			if (c == 1 && L[i][t]) {
				for (int j = 1; j <= N; j++)
					G[j][i] = 0;
				ans[mv--] = L[i][t];
				lv[i] = V[L[i][t]] = 1;
				flag = false;
			}
		}

		if (flag)
			break;
	}

	for (int i = 1; i <= M; i++)
		if (V[i] == 0)
			ans[mv--] = i;

	for (int i = 1; i <= M; i++)
		printf("%d%c", ans[i], i == M ? '\n' : ' ');
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init ();
		solve ();
	}
	return 0;
}
