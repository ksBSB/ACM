#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 1005;
const int inf = 0x3f3f3f3f;
typedef pair<int,int> pii;

char S[maxn];
int N, dp[maxn];
vector<int> G[maxn];

void init () {
	scanf("%s", S + 1);
	N = strlen(S + 1);
	for (int i = 0; i <= N; i++)
		G[i].clear();

	queue<pii> que;
	for (int i = 1; i <= N; i++)
		que.push(make_pair(i, i));
	for (int i = 1; i < N; i++) if (S[i] == S[i+1])
		que.push(make_pair(i, i + 1));

	while (!que.empty()) {
		int l = que.front().first;
		int r = que.front().second;
		que.pop();
		G[l-1].push_back(r);

		l--, r++;
		if (l == 0 || r > N) continue;
		if (S[l] == S[r])
			que.push(make_pair(l, r));
	}
}

int solve () {
	memset(dp, inf, sizeof(dp));
	dp[0] = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < G[i].size(); j++)
			dp[G[i][j]] = min(dp[G[i][j]], dp[i] + 1);
	}
	return dp[N];
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();
		printf("Case %d: %d\n", kcas, solve());
	}
	return 0;
}
