#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 50005;
const int inf = 0x3f3f3f3f;

int dp[maxn];

int idx(int* c) {
	int ret = 0;
	for (int i = 0; i < 6; i++)
		ret = ret * 6 + c[i];
	return ret;
}

void ridx(int s, int* c) {
	for (int i = 5; i >= 0; i--) {
		c[i] = s % 6;
		s /= 6;
	}
}

void presolve() {

	int c[10], t[10];
	for (int i = 0; i < 6; i++) c[i] = i;
	int s = idx(c);

	memset(dp, inf, sizeof(dp));
	dp[s] = 0;
	
	queue<int> que;
	que.push(s);

	while (!que.empty()) {
		s = que.front();
		que.pop();

		ridx(s, c);
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				memcpy(t, c, sizeof(t));
				for (int k = 0; k < 6; k++) if (t[k] == i) t[k] = j;
				int v = idx(t);
				if (dp[v] > dp[s] + 1) {
					dp[v] = dp[s] + 1;
					que.push(v);
				}
			}
		}
	}
}

int G[10][10], C[10];
char a[200], b[200];

int main () {
	presolve();
	while (scanf("%s%s", a, b) == 2) {
		memset(G, 0, sizeof(G));
		memset(C, 0, sizeof(C));

		int n = strlen(a);
		for (int i = 0; i < n; i++) {
			int u = b[i] - '1', v = a[i] - '1';
			C[u]++;
			G[u][v]++;
		}

		int ans = inf, t[10];
		for (int s = 0; s < maxn; s++) {
			ridx(s, t);
			int tmp = dp[s];
			for (int i = 0; i < 6; i++)
				tmp += C[i] - G[i][t[i]];
			ans = min(ans, tmp);
		}
		printf("%d\n", ans);
	}
	return 0;
}
