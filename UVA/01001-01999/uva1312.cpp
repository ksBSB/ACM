#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 105;

struct point {
	int x, y;
}p[N];
int n, w, h, dy[N];

bool cmp(const point& a, const point& b) {
	if (a.x != b.x) return a.x < b.x;
	return a.y < b.y;
}

void init() {
	scanf("%d%d%d", &n, &w, &h);
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &p[i].x, &p[i].y);
		dy[i] = p[i].y;
	}
	dy[n] = 0; dy[n+1] = h;
	sort(dy, dy + n + 2);
	sort(p, p + n, cmp);
}

void solve () {
	int ansx, ansy, ans = 0;
	int m = unique(dy, dy + n + 2) - dy;
	for (int i = 0; i < m; i++) {
		for (int j = i + 1; j < m; j++) {
			int maxy = dy[j], miny = dy[i];
			int hh = maxy - miny, ww = 0, tmp = 0;
			for (int k = 0; k < n; k++) {
				if (p[k].y <= miny || p[k].y >= maxy) continue;
				ww = p[k].x - tmp;
				if (ans < min(ww, hh)) {
					ans = min(ww, hh);
					ansx = tmp; ansy = miny;
				}

				tmp = p[k].x;
			}

			ww = w - tmp;
			if (ans < min(ww, hh)) {
				ans = min(ww, hh);
				ansx = tmp; ansy = miny;
			}
		}
	}
	printf("%d %d %d\n", ansx, ansy, ans);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		solve();
		if (cas) printf("\n");
	}
	return 0;
}
