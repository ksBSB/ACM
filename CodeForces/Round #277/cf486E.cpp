#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef pair<int, int> pii;
const int maxn = 1e5;

int N, A[maxn + 5], dp[maxn + 5], ct[maxn + 5], f[maxn + 5], v[maxn + 5];

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int lc[maxn << 2], rc[maxn << 2];
pii s[maxn << 2];

pii merge(pii a, pii b) {
	if (a.first == b.first)
		return make_pair(a.first, a.second + b.second);
	else
		return a.first > b.first ? a : b;
}

void build (int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;

	if (l == r) {
		s[u] = make_pair(0, 1);
		return;
	}

	int mid = (l + r) >> 1;
	build(lson(u), l, mid);
	build(rson(u), mid + 1, r);
	s[u] = merge(s[lson(u)], s[rson(u)]);
}

pii query(int u, int l, int r) {
	if (l <= lc[u] && rc[u] <= r)
		return s[u];

	int mid = (lc[u] + rc[u]) >> 1;
	pii ret = make_pair(0, 1);;
	if (l <= mid)
		ret = merge(ret, query(lson(u), l, r));
	if (r > mid)
		ret = merge(ret, query(rson(u), l, r));
	return ret;
}

void modify(int u, int x, pii d) {
	if (lc[u] == x && rc[u] == x) {
		s[u] = merge(s[u], d);
		return ;
	}

	int mid = (lc[u] + rc[u]) >> 1;
	if (x <= mid)
		modify(lson(u), x, d);
	else
		modify(rson(u), x, d);
	s[u] = merge(s[lson(u)], s[rson(u)]);
}

int main () {

	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &A[i]);

	build(1, 0, maxn);
	for (int i = 1; i <= N; i++) {
		pii u = query(1, 0, A[i]-1);
		dp[i] = u.first + 1;
		modify(1, A[i], make_pair(dp[i], 1));
	}
	int ans = query(1, 1, maxn).first;

	f[ans + 1] = maxn + 1;
	for (int i = N; i; i--) {
		if (A[i] < f[dp[i]+1]) {
			v[i] = 1;
			ct[dp[i]]++;
			f[dp[i]] = max(f[dp[i]], A[i]);
		}
	}

	for (int i = 1; i <= N; i++) {
		if (v[i])
			printf("%c", '2' + (ct[dp[i]] == 1 ? 1 : 0));
		else
			printf("1");
	}
	printf("\n");
	return 0;
}
