#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e6+5;
const int INF = 0x3f3f3f3f;

int R, L, c[maxn], g[maxn];
int n, arr[maxn], pos[maxn], vis[maxn];

void  input () {
	scanf("%d", &n);
	memset(vis, -1, sizeof(vis));

	int cnt = 0, mv = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
		if (arr[i] == 0) {
			mv++;
			pos[cnt++] = i;
			c[mv-1]++;
		} else {
			int k = min(cnt, arr[i]);
			mv = mv + arr[i];
			for (int j = 1; j <= k; j++) {
				int u = mv - j;
				vis[u] = i - pos[cnt-j] - j + 1;
				g[u] += vis[u];
				c[u]++;
			}
		}
	}

	reverse(arr, arr+n);

	cnt = 0;
	for (int i = 0; i < n; i++) {
		if (arr[i] == 0) {
			mv--;
			pos[cnt++] = i;
		} else {
			int k = min(cnt, arr[i]);
			mv = mv - arr[i];
			for (int j = 0; j < k; j++) {
				int u = mv + j;
				if (vis[u] == -1) {
					vis[u] = i - pos[cnt-j-1] - j;
					g[u] += vis[u];
					c[u]++;
				} else {
					int tmp = i - pos[cnt-j-1] - j;
					g[u] += min(0, tmp - vis[u]);
				}
			}
		}
	}
}

void init () {
	scanf("%d%d", &R, &L);
	memset(c, 0, sizeof(c));
	memset(g, 0, sizeof(g));

	for (int i = 0; i < R; i++)
		input();
}

void solve () {
	int ans = INF, cnt = 0;
	for (int i = 0; i < L; i++) {
		if (c[i] == R) {
			if (g[i] < ans) {
				cnt = 0;
				ans = g[i];
			}

			if (g[i] == ans)
				vis[cnt++] = i;
		}
	}

	/*
	printf("%d\n%d", ans, vis[0]);
	for (int i = 1; i < cnt; i++)
		printf(" %d", vis[i]);
	printf("\n");
	*/
	printf("%d\n", ans);
	for (int i = 0; i < cnt; i++)
		printf("%d ", vis[i]);
	printf("\n");
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		solve();
	}
	return 0;
}
