#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 10005;
const int maxm = 5;
const int maxs = (1<<5)-1;
const int INF = 0x3f3f3f3f;

int N, K;
int num[maxn][maxm+5], rec[maxs+5];

void cal (int a[maxm+5]) {

	for (int s = 0; s <= maxs; s++) {
		int tmp = 0;
		for (int j = 0; j < maxm; j++)
			if (s&(1<<j))
				tmp += a[j];
		rec[s] = max(rec[s], tmp);
	}
}

void init () {
	scanf("%d%d", &N, &K);
	K = min(K, maxm);
	memset(rec, 0, sizeof(rec));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < maxm; j++)
			scanf("%d", &num[i][j]);
		cal(num[i]);
	}
}

int dfs (int d, int S) {
	if (d == K)
		return S ? -INF : 0;

	if (S == 0)
		return -INF;

	int ans = 0;
	for (int s0 = S; s0; s0 = (s0-1)&S)
		ans = max(ans, dfs(d+1, s0^S) + rec[s0]);
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%d\n", dfs(0, maxs));
	}
	return 0;
}
