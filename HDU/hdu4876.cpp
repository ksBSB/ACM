#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 200;
const int maxc = 25;
const int maxs = 1<<20;
const int maxt = 20005;

bool flag;
int ans, rec, dp[maxs+5];
int N, K, L, arr[maxc];
int vec[maxn][maxt], c[maxn];

inline int bitcount (int s) {
	return s == 0 ? 0 : bitcount(s/2) + (s&1);
}

void dfs (int d, int s, int val, int f) {
	if (d == K + 1)
		return;

	vec[val][c[val]++] = s;

	for (int i = f + 1; i < N; i++)
		dfs (d+1, s|(1<<i), val^arr[i], i);
}

void init () {
	flag = true;
	ans = rec = 0;
	memset(c, 0, sizeof(c));
	memset(dp, 0, sizeof(dp));

	for (int i = 0; i < N; i++)
		scanf("%d", &arr[i]);

	dfs(0, 0, 0, -1);
}

int check (int* a) {
	int v[maxn];
	memset(v, 0, sizeof(v));

	for (int m = 1; m <= K; m++) {
		int tmp = a[0];
		for (int i = 1; i < m; i++)
			tmp ^= a[i];

		for (int i = 0; i < K; i++) {
			v[tmp] = 1;
			tmp ^= (a[i] ^ a[i+m]);
		}
	}

	int ans = L;
	while (v[ans] && ans < maxn)
		ans++;
	return ans - 1;
}

void judge (int s) {
	int cnt = 0, a[2*maxn];

	for (int i = 0; i < N; i++) {
		if (s&(1<<i))
			a[cnt++] = arr[i];
	}

	sort(a + 1, a + cnt);
	do {
		for (int i = 0; i < cnt; i++)
			a[i+cnt] = a[i];

		ans = max(ans, check(a));
	} while (next_permutation(a + 1, a + cnt));
}
/*
*/

void solve (int d, int s) {
	int cnt = bitcount(s);

	rec = max(d, rec);
	if (cnt >= K || d >= maxn) {
		if (cnt == K) {
			judge(s);
			flag = false;
		}
		return;
	}

	for (int i = 0; i < c[d]; i++) {
		int s0 = (s | vec[d][i]);
		if (dp[s0]) continue;
		solve(d+1, s0);
		dp[s0] = 1;
	}
}

int main () {
	while (scanf("%d%d%d", &N, &K, &L) == 3) {
		init();
		solve(L, 0);

		if (flag)
			ans = rec - 1;
		printf("%d\n", ans < L ? 0 : ans);
	}
	return 0;
}
