#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>

using namespace std;
const int maxn = 1e5+5;
const int INF = 0x3f3f3f3f;

struct point {
	int x, y, flag;
}p[maxn*2];
int N, M;

bool cmp (const point& a, const point& b) {
	return a.y < b.y;
}

void init () {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d%d", &p[i].x, &p[i].y);
		p[i].flag = 0;
	}

	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		scanf("%d%d", &p[i+N].x, &p[i+N].y);
		p[i+N].flag = 1;
	}

}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		int ans = INF, now = INF;
		sort(p, p + N + M, cmp);
		for (int i = 0; i < N + M; i++) {
			if (p[i].flag)
				now = min(now, p[i].x - p[i].y);
			else
				ans = min(ans, now - p[i].x + p[i].y);
		}

		now = INF;
		reverse(p, p + N + M);
		for (int i = 0; i < N + M; i++) {
			if (p[i].flag)
				now = min(now, p[i].x + p[i].y);
			else
				ans = min(ans, now - p[i].x - p[i].y);
		}
		printf("%d\n", ans);
	}
	return 0;
}
