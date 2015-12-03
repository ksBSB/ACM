#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 1e5;

double dp[maxn + 5];
vector<int> G[maxn + 5];

void init () {
	for (int i = 2; i <= maxn; i++)
		for (int j = i; j <= maxn; j += i)
			G[j].push_back(i);
	dp[1] = 0;
	for (int i = 2; i <= maxn; i++) {
		double s = 0;
		for (int j = 0; j < G[i].size(); j++)
			s += dp[i / G[i][j]];
		dp[i] = (G[i].size() + 1 + s) / G[i].size();
	}
}

int main () {
	init();

	int cas, n;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%d", &n);
		printf("Case %d: %.6lf\n", kcas, dp[n]);
	}
	return 0;
}
