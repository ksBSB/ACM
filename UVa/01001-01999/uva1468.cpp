#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;
const int N = 1e4+5;
const int INF = 0x3f3f3f3f;
typedef long long ll;

int m, n, yMax[N*6], yMin[N*6];
int ax, ay, bx, by, py[N*6];

void init () {
	scanf("%d%d", &m, &n);
	scanf("%d%d%d%d", &ax, &ay, &bx, &by);

	if (ax > bx) swap (ax, bx);

	for (int i = ax+1; i < bx; i++) {
		yMax[i] = -INF;
		yMin[i] = INF;
	}

	int x, y;
	for (int i = 2; i < n; i++) {
		scanf("%d%d", &x, &y);

		if (y >= ay) yMin[x] = min (y, yMin[x]);
		if (y <= ay) yMax[x] = max (y, yMax[x]);
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init ();

		for (int i = ax + 1; i < bx; i++)
			py[i] = min (yMin[i] - ay, ay - yMax[i]);

		py[ax] = py[bx] = 0;
		for (int i = ax + 1; i < bx; i++)
			py[i] = min (py[i], py[i-1] + 1);
		for (int i = bx - 1; i > ax; i--)
			py[i] = min (py[i], py[i+1] + 1);

		ll ans = 0;
		for (int i = ax + 1; i < bx; i++) {
			if (py[i]) {
				ans++;

				ans += min (py[i] - 1, m - ay - 1);
				ans += min (py[i] - 1, ay);
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
