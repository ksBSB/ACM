#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 20;
const int maxs = (1<<16) + 6;
const int inf = 0x3f3f3f3f;

int N, dp[maxs], vis[maxs];
char str[maxn];

bool judge(int s) {
	int a[maxn], n = 0;
	for (int i = 0; i < N; i++) if (s&(1<<i))
		a[n++] = i;
	for (int i = 0; i < n/2; i++)
		if (str[a[i]] != str[a[n-i-1]]) return false;
	return true;
}

void init () {
	scanf("%s", str);
	N = strlen(str);
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < (1<<N); i++)
		if (judge(i)) vis[i] = 1;
}

int solve () {
	memset(dp, inf, sizeof(dp));
	dp[0] = 0;
	for (int i = 0; i < (1<<N); i++) {
		int s = i^((1<<N)-1);
		for (int j = s; j; j = (j-1)&s) {
			if (vis[j]) {
				int v = i|j;
				dp[v] = min(dp[v], dp[i]+1);
			}
		}
	}
	return dp[(1<<N)-1];
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
