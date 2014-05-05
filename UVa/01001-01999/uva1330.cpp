#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int N = 1005;
int n, m, g[N][N];

void init() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			char ch = getchar();
			while (ch != 'R' && ch != 'F') ch = getchar();
			if (ch == 'R') g[i][j] = 0;	
			else g[i][j] = g[i-1][j] + 1;
		}
	}
}

int solve() {
	int ans = 0, l[N], r[N];
	for (int i = 1; i <= n; i++) {
		g[i][0] = g[i][m+1] = -1;
		for (int j = 1; j <= m; j++) l[j] = r[j] = j;

		for (int j = 1; j <= m; j++) {
			while (g[i][j] <= g[i][l[j]-1]) l[j] = l[j] - 1; 
		}

		for (int j = m; j; j--) {
			while (g[i][j] <= g[i][r[j]+1]) r[j] = r[j] + 1;
			ans = max(ans, g[i][j] * (r[j] - l[j] + 1));
		}
	}
	return ans * 3;
}

int main() {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}
