#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 50005;
const int inf = 0x3f3f3f3f;
#define lowbit(x) ((-x)&(x))

struct Pi {
	int idx, L, R;
}P[maxn];

int N, ans, rans, dp[maxn], pre[maxn];
int bw, sy[maxn], ty[maxn << 1], sz[maxn], tz[maxn];

bool cmp (const int& a, const int& b) {
	return P[a].L > P[b].L;
}

namespace Bit {
	int n, fenw[maxn], rec[maxn];

	void init (int k) {
		n = k;
		memset(fenw, 0, (n + 1) * sizeof(int));
	}

	void add (int x, int k, int id) {
		while (x <= n) {
			if (fenw[x] == k)
				rec[x] = min(rec[x], id);
			else if (fenw[x] < k)
				fenw[x] = k, rec[x] = id;
			x += lowbit(x);
		}
	}

	int search (int x, int& id) {
		int ret = id = 0;
		while (x) {
			if (fenw[x] > ret)
				ret = fenw[x], id = rec[x];
			else if (fenw[x] == ret)
				id = min(id, rec[x]);
			x -= lowbit(x);
		}
		return ret;
	}
};

void init () {
	bw = ans = rans = 0;
	for (int i = 1; i <= N; i++)
		scanf("%d", &P[i].L);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &P[i].R);
		sy[i] = i, dp[i] = 1;
	}
	sort(sy + 1, sy + N + 1, cmp);
}

void solve (int l, int r) {
	if (l == r) {
		if (dp[l] > ans)
			ans = dp[l], rans = l;
		else if (dp[l] == ans)
			rans = min(rans, l);
		sz[l] = P[l].R;
		return;
	}

	int mid = (l + r) >> 1, len = r - l + 1;
	int ml = l, mr = mid + 1;
	memcpy(ty + bw, sy + l, len * sizeof(int));
	for (int i = 0; i < len; i++) {
		if (ty[bw+i] <= mid)
			sy[ml++] = ty[bw+i];
		else
			sy[mr++] = ty[bw+i];
	}
	bw += len;
	solve(mid + 1, r);
	int n = r - mid, limt = bw, pos, ri = mid + 1;
	bw -= len;

	Bit::init(n);
	//printf("%d %d %d:\n", l, r, len);
	for (int i = limt - 1; i >= bw; i--) {
		if (ty[i] > mid) {
			pos = lower_bound(sz + ri, sz + ri + n, P[ty[i]].R) - (sz + ri);
			Bit::add(n - pos, dp[ty[i]], ty[i]);
			//printf("add: %d %d %d\n", n - pos, dp[i], i);
			continue;
		}

		pos = lower_bound(sz + ri, sz + ri + n, P[ty[i]].R) - (sz + ri);
		
		//printf("check:%d\n", pos);

		if (pos >= 0) {
			int tmp;
			int ret = Bit::search(n - pos, tmp) + 1;
			//printf("search:%d %d %d\n", n - pos, ret, tmp);

			if (dp[ty[i]] < ret)
				dp[ty[i]] = ret, pre[ty[i]] = tmp;
			else if (dp[ty[i]] == ret)
				pre[ty[i]] = min(pre[ty[i]], tmp);
		}
	}

	solve(l, mid);
	merge(sz + l, sz + ri, sz + ri, sz + l + len, tz);
	memcpy(sz + l, tz, len * sizeof(int));
}

int main () {
	while (scanf("%d", &N) == 1) {
		init();
		solve(1, N);
		printf("%d\n", ans);
		for (int i = 1; i <= ans; i++) {
			printf("%d%c", rans, i == ans ? '\n' : ' ');
			rans = pre[rans];
		}
	}
	return 0;
}
