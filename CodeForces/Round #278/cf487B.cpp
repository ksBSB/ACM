#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 5;
const int maxr = 20;
const int inf = 0x3f3f3f3f;

int ca, cd, AS[maxn], DS[maxn];
int N, S, L, Db[maxn][maxr], Ds[maxn][maxr], dp[maxn];
vector<int> Arr;

void init(const vector<int>& arr) {
	int n = arr.size();
	for (int i = 1; i < n; i++)
		Db[i][0] = Ds[i][0] = arr[i];
	for (int j = 1; (1<<j) <= n; j++) {
		for (int i = 0; i + (1<<j) - 1 < n; i++) {
			Ds[i][j] = min(Ds[i][j-1], Ds[i+(1<<(j-1))][j-1]);
			Db[i][j] = max(Db[i][j-1], Db[i+(1<<(j-1))][j-1]);
		}
	}
}

int query(int l, int r) {
	int k = 0;
	while ((1<<(k+1)) <= r - l + 1)
		k++;
	return max(Db[l][k], Db[r-(1<<k)+1][k]) - min(Ds[l][k], Ds[r-(1<<k)+1][k]);
}

void solve() {
	memset(dp, inf, sizeof(dp));
	int mv = dp[0] = 0;

	for (int i = L; i <= N; i++) {
		while (i - mv >= L && (query(mv + 1, i) > S || dp[mv] == inf))
			mv++;

		if (i - mv >= L)
			dp[i] = min(dp[i], dp[mv] + 1);
//		printf("%d\n", dp[i]);
	}
	if (dp[N] == inf)
		dp[N] = -1;
	printf("%d\n", dp[N]);
}

int main () {
	int x;
	scanf("%d%d%d", &N, &S, &L);
	Arr.push_back(0);
	for (int i = 0; i < N; i++) {
		scanf("%d", &x);
		Arr.push_back(x);
	}
	init(Arr);

	solve();
	return 0;
}
