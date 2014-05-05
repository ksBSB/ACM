#include <stdio.h>
#include <string.h>

const int N = 105;
const int M = 15;

int p, c, m, b[N], w[N], ans[M];
int g[N][M], l[N][N], r[N][N];
int cnt[N], sum[N];

void init () {
	memset(l, 0, sizeof(l));
	memset(r, 0, sizeof(r));
	memset(cnt, 0, sizeof(cnt));
	memset(sum, 0, sizeof(sum));

	scanf("%d%d%d", &p, &c, &m);

	for (int i = 0; i < m; i++) {

		for (int j = 0; j < p; j++) {
			scanf("%d", &g[i][j]);
			r[i][g[i][j]]++;
		}
		scanf("%d%d", &b[i], &w[i]);
	}
}

inline bool judge (int x, int d) {
	
	for (int i = 0; i < m; i++) {
		if (p - d < b[i] - cnt[i]) return false;
		if (x == g[i][d]) {
			if (b[i] == cnt[i]) return false;
		} else if (l[i][x] < r[i][x]) {
			if (sum[i] >= w[i] + b[i]) return false;
		}
	}
	return true;
}

inline void set (int x, int d, int flag) {

	if (flag > 0) {
		for (int i = 0; i < m; i++) {
			if (x == g[i][d])
				cnt[i]++;

			if (l[i][x] < r[i][x])
				sum[i]++;
			l[i][x]++;
		}
	} else {
		for (int i = 0; i < m; i++) {
			if (x == g[i][d])
				cnt[i]--;
			l[i][x]--;
			if (l[i][x] < r[i][x])
				sum[i]--;
		}
	}
}

bool dfs (int d) {
	if (d == p) {
		for (int i = 0; i < m; i++)
			if (cnt[i] != b[i] || sum[i] != w[i] + b[i]) return false;
		return true;
	}

	for (int i = 1; i <= c; i++) {

		if (!judge(i, d)) continue;
		set(i, d, 1);

		ans[d] = i;
		if (dfs(d+1)) return true;

		set(i, d, -1);
	}
	return false;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init ();
		bool flag = dfs(0);

		if (flag) {
			printf("%d", ans[0]);
			for (int i = 1; i < p; i++)
				printf(" %d", ans[i]);
			printf("\n");
		} else 
			printf("You are cheating!\n");
	}
	return 0;
}
