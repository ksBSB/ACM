#include <stdio.h>
#include <string.h>

const int N = 20005;

int n, q, d, ti, v[N], l[N], r[N], cnt[N], rec[N];

void init() {
	scanf("%d%d%d", &n, &q, &d);
	ti = 0;
	memset(cnt, 0, sizeof(cnt));
	memset(rec, 0, sizeof(rec));
	memset(v, 0, sizeof(v));
	memset(l, 0, sizeof(l));
	memset(r, 0, sizeof(r));
}

void add(int x, int val) {
	while (x <= n) {
		v[x] += val;
		x += (x & (-x));
	}
}

int sum(int x) {
	int ans = 0;
	while (x > 0) {
		ans += v[x];
		x -= (x &(-x));
	}
	return ans;
}

void solve() {
	int a, b;
	char o[10];

	for (int i = 0; i < q; i++) {
		scanf("%s", o);
		
		if (o[0] == 'A') {
			scanf("%d%d", &a, &b);
			add(a, 1); add(b+1, -1);
			l[ti] = a, r[ti] = b;
			ti++;
		} else {
			scanf("%d", &a);
			for (int j = rec[a]; j < ti; j++) if (l[j] <= a && r[j] >= a) {
				rec[a] = j + d;
				cnt[a]++;
				j += d - 1;
			}
			printf("%d\n", sum(a) - cnt[a]);
		}
	}
}

int main() {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		printf("Case %d:\n", i);
		init();
		solve();
	}
	return 0;
}
