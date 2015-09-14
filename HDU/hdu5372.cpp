#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 2 * 1e5 + 5;
#define lowbit(x) ((x)&(-x))

struct Bit {
	int n, fenw[maxn];

	void init (int k) {
		n = k;
		memset(fenw, 0, (n + 1) * sizeof(int));
	}

	void add (int x, int d) {
		while (x <= n) {
			fenw[x] += d;
			x += lowbit(x);
		}
	}

	int sum (int x) {
		int ret = 0;
		while (x) {
			ret += fenw[x];
			x -= lowbit(x);
		}
		return ret;
	}
}L, R;

int N, Q, op[maxn], l[maxn], r[maxn], ID[maxn];
int cntL, cntR, left[maxn], right[maxn];

void init () {
	Q = cntL = cntR = 0;
	for (int i = 1; i <= N; i++) {
		scanf("%d%d", &op[i], &l[i]);

		if (op[i] == 0) {
			ID[++Q] = i;
			r[i] = l[i] + Q;
			left[cntL++] = l[i];
			right[cntR++] = r[i];
		}
	}

	sort(left, left + cntL);
	cntL = unique(left, left + cntL) - left;
	sort(right, right + cntR);
	cntR = unique(right, right + cntR) - right;

	L.init(cntL);
	R.init(cntR);
}

void solve () {
	for (int i = 1; i <= N; i++) {
		if (op[i]) {
			int v = ID[l[i]];
			int p = lower_bound(left, left + cntL, l[v]) - left + 1;
			int q = lower_bound(right, right + cntR, r[v]) - right + 1;
			L.add(p, -1);
			R.add(q, -1);
			Q++;
		} else {
			int p = lower_bound(left, left + cntL, l[i]) - left + 1;
			int q = lower_bound(right, right + cntR, r[i]) - right + 1;
			int ans = R.sum(q) - L.sum(p-1);
			L.add(p, 1);
			R.add(q, 1);
			printf("%d\n", ans);
		}
	}
}

int main () {
	int cas = 1;
	while (scanf("%d", &N) == 1) {
		init ();
		printf("Case #%d:\n", cas++);
		solve ();
	}
	return 0;
}
