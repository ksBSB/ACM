#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;
const int N = 105;
const int M = 3005;
const int need[N] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int n, m;
char dp[N][M][55];

bool cmp(char* a, char* b) {
	int la = strlen(a);
	int lb = strlen(b);
	if (la != lb)
		return la < lb;
	return strcmp(a, b) < 0;
}

void solve (char* a, char* b, int k) {
	char tmp[55];
	memset(tmp, 0, sizeof(tmp));
	strcpy(tmp, b);

	int len = strlen(tmp);
	if (tmp[0] == '0')
		tmp[0] = '0' + k;
	else
		tmp[len] = '0' + k;

	if (cmp(a, tmp))
		strcpy(a, tmp);
}

int main () {
	int cas = 1;
	while (scanf("%d", &n) == 1 && n) {
		scanf("%d", &m);

		char ans[55];
		memset(ans, 0, sizeof(ans));
		memset(dp, 0, sizeof(dp));

		dp[0][0][0] = '0';
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= m; j++) {
				if (strlen(dp[i][j]) == 0)
					continue;

				for (int k = 0; k < 10; k++) {
					if (i + need[k] > n) 
						continue;

					int t = (j*10 + k)%m;
					solve(dp[i+need[k]][t], dp[i][j], k);
				}
			}
			if (i && cmp(ans, dp[i][0]))
				memcpy(ans, dp[i][0], sizeof(dp[i][0]));
		}

		printf("Case %d: ", cas++);
		if (ans[0] == '\0')
			printf("-1\n");
		else
			printf("%s\n", ans);
	}
	return 0;
}
