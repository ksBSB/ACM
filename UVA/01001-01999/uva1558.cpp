#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxs = (1<<20)-1;

int cnt, ans[30], dp[maxs+10];

int solve (int s, int x) {
	for (int i = x; i <= 20; i += x) {
		if (s&(1<<(i-2)))
			s ^= (1<<(i-2));
	}

	/*
	for (int i = 2; i + x < 20; i++) {
		if ( (s&(1<<(i-2))) == 0 && (s&(1<<(i+x-2))) )
			s ^= (1<<(i+x-2));
	}
	*/
	for (int i = 2; i <= 20; i++) {
		if (s&(1<<(i-2))) {
			for (int j = x; i - j >= 2; j += x) {
				if (!(s&(1<<(i-j-2)))) {
					s ^= (1<<(i-2));
					break;
				}
			}
		}
	}
	return s;
}

bool dfs (int s) {

	if (dp[s] != -1)
		return dp[s];

	for (int i = 2; i <= 20; i++) {
		if ((s&(1<<(i-2))) && (dfs(solve(s, i)) == false))
			return dp[s] = 1;
	}

	return dp[s] = 0;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int k = 1; k <= cas; k++) {
		int x, n, s = 0;
		memset(dp, -1, sizeof(dp));
		cnt = dp[0] = 0;

		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &x);
			s |= (1<<(x-2));
		}

		for (int i = 2; i <= 20; i++) {
			if ((s&(1<<(i-2))) && dfs(solve(s, i)) == false)
				ans[cnt++] = i;
		}

		printf("Scenario #%d:\n", k);
		if (cnt) {
			printf("The winning moves are:");
			for (int i = 0; i < cnt; i++)
				printf(" %d", ans[i]);
			printf(".\n");
		} else
			printf("There is no winning move.\n");
		printf("\n");
	}
	return 0;
}
