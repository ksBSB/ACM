#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 105;

struct point {
	int x, y;
	bool operator < (const point& c) const {
		return x < c.x;
	}
}p[N];
int n, dy[N];

void init () {
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &p[i].x, &p[i].y);
		dy[i] = p[i].y;
	}
	sort(p, p + n);
	sort(dy, dy + n);
}

int solve () {
	int m = unique(dy, dy + n) - dy;
	if (m <= 2) return n;
	
	int ans = 0, v[N], in[N], on[N];

	for (int i = 0; i < m; i++) {
		for (int j = i + 1; j < m; j++) {
			int miny = dy[i], maxy = dy[j], k = -1;
			memset(v, 0, sizeof(v));
			memset(in, 0, sizeof(in));
			memset(on, 0, sizeof(on));

			for (int t = 0; t < n; t++) {
				if (!t || p[t].x != p[t-1].x) {
					k++;
					v[k] = (k == 0 ? 0 : v[k-1] + on[k-1] - in[k-1]);
				}

				if (p[t].y > miny && p[t].y < maxy) in[k]++;
				if (p[t].y >= miny && p[t].y <= maxy) on[k]++;
			}

			if (k <= 1) return n;

			int tmp = 0;
			for (int t = 0; t <= k; t++) {
				ans = max(ans, v[t] + on[t] + tmp);
				tmp = max(tmp, in[t] - v[t]);
			}
		}
	}
	return ans;
}

int main () {
	int cas = 1;
	while (scanf("%d", &n) == 1 && n) {
		init ();
		printf("Case %d: %d\n", cas++, solve());
	}
	return 0;
}
