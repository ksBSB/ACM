#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define lowbit(x) ((-x)&(x))
typedef long long ll;
const int maxn = 1e5 + 5;
const ll mod = 1 << 30;

struct Pi {
	int x, y, z;
	bool operator < (const Pi& u) const {
		if (x != u.x)
			return x < u.x;
		if (y != u.y)
			return y < u.y;
		return z < u.z;
	}
}P[maxn];

bool cmp (const int a, const int b) {
	return P[a].y < P[b].y;
}

int N, ans, dp[maxn], sz[maxn], tz[maxn];
int bw, ty[maxn << 1], sy[maxn];
ll cans, num[maxn];

namespace Bit {
	int n, fenw[maxn];
	ll cnt[maxn];

	void init (int k) {
		n = k;
		memset(fenw, 0, (n + 1) * sizeof(int));
	}

	void add (int x, int k, ll d) {
		while (x <= n) {
			if (fenw[x] == k)
				cnt[x] = (cnt[x] +  d) % mod;
			else if (fenw[x] < k)
				cnt[x] = d, fenw[x] = k;
			x += lowbit(x);
		}
	}

	void search (int x, int& ret, ll& sum) {
		ret = sum = 0;
		while (x) {
			if (fenw[x] == ret)
				sum += cnt[x];
			else if (fenw[x] > ret)
				ret = fenw[x], sum = cnt[x];
			x -= lowbit(x);
		}
	}
};

void solve (int l, int r) {
	if (l == r) {
		if (dp[l] > ans) {
			ans = dp[l];
			cans = num[l];
		} else if (dp[l] == ans)
			cans = (cans + num[l]) % mod;
		sz[l] = P[l].z;
		return ;
	}

	int mid = (l + r) >> 1, len = r - l + 1;
	int pl = l, pr = mid + 1, n = mid - l + 1;
	memcpy(ty + bw, sy + l, len * sizeof(int));
	for (int i = 0; i < len; i++) {
		if (ty[bw+i] <= mid)
			sy[pl++] = ty[bw + i];
		else
			sy[pr++] = ty[bw + i];
	}
	bw += len;
	solve(l, mid);
	int limt = bw, pos;
	bw -= len;

	Bit::init(n);
	//printf("%d %d: n = %d\n", l, r, n);
	for (int i = bw; i < limt; i++) {
		if (ty[i] <= mid) {
			pos = lower_bound(sz + l, sz + l + n, P[ty[i]].z) - (sz+l)+1;
			Bit::add(pos, dp[ty[i]], num[ty[i]]);
			//		printf("add:%d %d\n", pos, dp[ty[i]]);
			continue;
		}
		pos = lower_bound(sz + l, sz + l + n, P[ty[i]].z) - (sz+l);
		//	printf("check:%d\n", pos);

		if (pos >= n || sz[l+pos] > P[ty[i]].z)
			pos--;

		if (pos >= 0) {
			int ret;
			ll sum;
			Bit::search(pos + 1, ret, sum);
			ret++;
			//		printf("check:%d %d\n", pos, ret);
			if (ret > dp[ty[i]]) {
				dp[ty[i]] = ret;
				num[ty[i]] = sum;
			} else if (ret == dp[ty[i]] && ret != 1)
				num[ty[i]] = (num[ty[i]] + sum) % mod;
		}

	}

	solve(mid + 1, r);
	merge(sz + l, sz + l + n, sz + l + n, sz + l + len, tz);
	memcpy(sz + l, tz, len * sizeof(int));
}

void init () {
	memset(ty, 0, sizeof(ty));
	memset(tz, 0, sizeof(tz));
	memset(sz, 0, sizeof(sz));
	ans = bw = cans = 0;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d%d%d", &P[i].x, &P[i].y, &P[i].z);
	sort(P + 1, P + N + 1);
	for (int i = 1; i <= N; i++) {
		sy[i] = i;
		dp[i] = num[i] = 1;
	}
	sort(sy + 1, sy + N + 1, cmp);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init ();
		solve (1, N);
		//		for (int i = 1; i <= N; i++)
		//			printf("%d %d %d %d %lld\n", P[i].x, P[i].y, P[i].z, dp[i], num[i]);
		printf("%d %lld\n", ans, cans % mod);
	}
	return 0;
}
