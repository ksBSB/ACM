#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 55;

int N;
char G[maxn][maxn];

bool check(char a, char b) {
	return a == b || a == 'G';
}

int solve() {
	int ret = 0;
	for (int i = 1; i <= N; i++) {
		int m = strlen(G[i]+1);
		for (int j = 1; j <= m; j++) {
			if (check(G[i][j], 'R') && !check(G[i-1][j-1], 'R'))
				ret++;
			if (check(G[i][j], 'B') && !check(G[i-1][j+1], 'B'))
				ret++;
		}
	}
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while(cas--) {
		scanf("%d", &N);
		memset(G, 0, sizeof(G));
		for (int i = 1; i <= N; i++)
			scanf("%s", G[i] + 1);
		printf("%d\n", solve());
	}
	return 0;
}
