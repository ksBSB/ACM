#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 5 * 1e4 + 5;
const int INF = 0x3f3f3f3f;

struct point {
	int val, pos;
	point (int val = 0, int pos = 0) {
		this->val = val;
		this->pos = pos;
	}
}p[maxn];

inline bool sort_val (const point& a, const point& b) {
	return a.val < b.val;
}

inline bool sort_pos (const point& a, const point& b) {
	return a.pos < b.pos;
}

int N, M, v[maxn];

void init () {
	M = N;
	for (int i = 1; i <= N; i++)
		scanf("%d", &p[i].val);

	int mv = 1;
	for (int i = 2; i <= N; i++) {
		if (p[i].val != p[i-1].val) {
			p[++mv] = p[i];
			p[mv].pos = mv;
		}
	}

	N = mv;
	sort(p + 1, p + 1 + N, sort_val);

	mv = 0;
	int pre = -1;
	for (int i = 1; i <= N; i++) {
		if (p[i].val != pre) {
			pre = p[i].val;
			mv++;
		}
		p[i].val = mv;
	}
	sort(p + 1, p + 1 + N, sort_pos);
}

int dp[maxn], vis[maxn];

int solve () {
	if (N + 3 >= M)
		return N;

	vector<int> vec;
	memset(dp, INF, sizeof(dp));
	dp[0] = 0;
	dp[N] = N;

	int mv = 0;

	while (true) {
		int u = mv;

		if (u == N)
			return dp[u];

		int cnt = 0, ans = dp[u + 1];
		mv = u + 1;

		for (int i = u + 1; i <= N; i++) {
			if (vis[p[i].val] == 0) {
				cnt++;
				vis[p[i].val] = 1;
				vec.push_back(p[i].val);
			}

			if (cnt * cnt + dp[u] > dp[N])
				break;

			if (dp[i] > dp[u] + cnt * cnt)
				dp[i] = dp[u] + cnt * cnt;

			if (dp[i] <= ans) {
				ans = dp[i];
				mv = i;
			}
		}

		for (int i = 0; i < cnt; i++)
			vis[vec[i]] = 0;
		vec.clear();
	}
	return N;
}

int main () {
	while (scanf("%d", &N) == 1) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}
