#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 30;

int n, a[2][maxn][maxn];

int solve () {
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (a[0][i][j] == a[1][i][j])
				cnt++;
		}
	}
	return cnt;
}

void role(int b[maxn][maxn]) {
	int c[maxn][maxn];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			c[j][n-i-1] = b[i][j];
		}
	}
	memcpy(b, c, sizeof(c));
}

int main () {
	while (scanf("%d", &n) == 1 && n) {
		for (int k = 0; k < 2; k++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++)
					scanf("%d", &a[k][i][j]);
			}
		}

		int ans = 0;
		for (int i = 0; i < 4; i++) {
			ans = max(ans, solve());
			role(a[0]);
		}
		printf("%d\n", ans);
	}
	return 0;
}
