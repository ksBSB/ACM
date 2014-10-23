#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 55;
const int INF = 0x3f3f3f3f;
typedef pair<int,int> pii;

int N, M, g[maxn][maxn], dp[1<<12][12];
vector<pii> vec;

inline int dis(int i, int j) {
	return abs(vec[i].first - vec[j].first) + abs(vec[i].second - vec[j].second);
}

int solve () {

	int n = vec.size();
	int m = 1<<n;

	memset(dp, INF, sizeof(dp));
	dp[1][0] = 0;

	for (int i = 1; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (i&(1<<j)) {
				for (int k = 0; k < n; k++)
					dp[i|(1<<k)][k] = min(dp[i|(1<<k)][k], dp[i][j] + dis(j, k));
			}
		}
	}

	int ret = INF;
	for (int i = 0; i < n; i++)
		ret = min(ret, dp[m-1][i] + dis(0, i));
	return ret;
}

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		vec.clear();
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				scanf("%d", &g[i][j]);
				if (g[i][j] || (i == 0 && j == 0))
					vec.push_back(make_pair(i, j));
			}
		}
		printf("%d\n", solve());
	}
	return 0;
}
