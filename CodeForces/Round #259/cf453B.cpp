#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int maxn = 105;
const int sign[maxn] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};
const int INF = 0x3f3f3f3f;
const int sn = 1<<16;

int N, num[maxn], s[maxn];
int dp[maxn][sn+5], rec[maxn][sn+5];

inline int getstate (int a) {
	int u = 0;
	for (int i = 0; i < 16; i++) {
		while (a % sign[i] == 0) {
			a /= sign[i];
			u |= (1<<i);
		}
	}
	return u;
}

inline void put_ans (int d, int S) {
	if (d == 0)
		return;

	int u = rec[d][S];
	put_ans(d-1, S^s[u]);
	num[d] = u;
}

void solve () {
	memset(rec, -1, sizeof(rec));
	rec[0][0] = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < sn; j++) {
			if (rec[i][j] == -1)
				continue;

			for (int k = 1; k < 60; k++) {
				if (j&s[k])
					continue;

				int v = j|s[k];
				if (rec[i+1][v] == -1 || dp[i][j] + abs(k-num[i+1]) < dp[i+1][v]) {
					rec[i+1][v] = k;
					dp[i+1][v] = dp[i][j] + abs(k-num[i+1]);
				}
			}
		}
	}

	int ans = INF, id;
	for (int i = 0; i < sn; i++) {
		if (dp[N][i] < ans && rec[N][i] != -1) {
			ans = dp[N][i];
			id = i;
		}
	}

	put_ans(N, id);
	for (int i = 1; i < N; i++)
		printf("%d ", num[i]);
	printf("%d\n", num[N]);

}

int main () {
	for (int i = 1; i < 60; i++)
		s[i] = getstate(i);

	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &num[i]);

	solve();
	return 0;
}
