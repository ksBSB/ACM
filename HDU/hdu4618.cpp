#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 305;

int N, M, A[maxn][maxn];

void init () {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			scanf("%d", &A[i][j]);
}

bool dp[maxn][maxn][maxn];

bool find (int k) {
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			if (dp[k][i][j]) return true;
	return false;
}

int solve () {
	memset(dp, false, sizeof(dp));
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++) dp[1][i][j] = true;
	for (int i = 1; i < N; i++)
		for (int j = 1; j < M; j++) {
			if (A[i][j] == A[i+1][j] && A[i][j] == A[i][j+1] && A[i][j] == A[i+1][j+1])
				dp[2][i][j] = true;
		}

	int n = min(N, M);
	for (int k = 3; k <= n; k++) {
		for (int i = 1; i <= N-k+1; i++) {
			for (int j = 1; j <= M-k+1; j++) {
				if (dp[k-2][i+1][j+1]) {
					int ii = i + k - 1, jj = j + k - 1;
					bool flag = true;
					for (int t = 0; t < k / 2 && flag; t++) {
						if (A[i+t][j] != A[ii-t][j] || A[i+t][j] != A[i+t][jj])
							flag = false;
						if (A[i][j+t] != A[i][jj-t] || A[i][j+t] != A[ii][j+t])
							flag = false;
					}
					dp[k][i][j] = flag;
				}
			}
		}
	}

	while (!find(n)) n--;
	return n;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}
