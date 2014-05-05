#include <stdio.h>
#include <string.h>

const int N = 15;
const int diec[4][2] = { {0, 1}, {1, 0}, {-1, 0}, {0, -1} };

int n;
char g[N][N];

void init() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%s", g[i]);
}

bool judge(int x, int y, char ch) {
	for (int i = 0; i < 4; i++) {
		int p = x + diec[i][0], q = y + diec[i][1];
		if (p < 0 || p >= n) continue;
		if (q < 0 || q >= n) continue;

		if (g[p][q] == ch) return false;
	}
	return true;
}

void solve() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (g[i][j] == '.') {
				for (int k = 0; ; k++) {
					if (judge(i, j, 'A' + k)) {
						g[i][j] = 'A' + k;
						break;
					}
				}
			}
		}
	}

	for (int i = 0; i < n; i++)
		puts(g[i]);
}
int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		init();
		printf("Case %d:\n", i);
		solve();
	}
	return 0;
}
