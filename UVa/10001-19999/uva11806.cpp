#include <cstdio>
#include <cstring>

const int N = 500;
const int MOD = 1000007;

int n, m, k, C[N+10][N+10];

void init () {

	for (int i = 0; i < N; i++) {
		C[i][0] = C[i][i] = 1;
		for (int j = 1; j < i; j++)
			C[i][j] = (C[i-1][j-1] + C[i-1][j])%MOD;
	}
}

int main () {
	init ();
	
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		scanf("%d%d%d", &n, &m, &k);
		int ans = 0;

		for (int s = 0; s < 16; s++) {
			int cnt = 0, r = n, c = m;

			if (s&1) {
				r--;
				cnt++;
			}

			if (s&2) {
				r--;
				cnt++;
			}

			if (s&4) {
				c--;
				cnt++;
			}

			if (s&8) {
				c--;
				cnt++;
			}

			if (cnt&1)
				ans = (ans + MOD - C[r*c][k])%MOD;
			else
				ans = (ans + C[r*c][k])%MOD;
		}
		printf("Case %d: %d\n", i, ans);
	}

	return 0;
}
