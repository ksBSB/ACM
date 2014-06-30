#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;
const int N = 50;
const int M = 2005;
const int INF = 0x3f3f3f3f;

struct state {
	int x, y;
}c[M], h[M];

int n, m, cntC, cntH;
char s[N];

void init () {
	cntC = cntH = 0;

	for (int i = 0; i < n; i++) {
		scanf("%s", s);

		for (int j = 0; j < m; j++) {
			if (s[j] == 'C') {
				c[cntC].x = i;
				c[cntC].y = j;
				cntC++;
			} else if (s[j] == 'H') {
				h[cntH].x = i;
				h[cntH].y = j;
				cntH++;
			}
		}
	}
}

inline int Count (int a, int b) {
	return abs(h[a].x - c[b].x) + abs(h[a].y - c[b].y);
}

bool cmp (const state& a, const state& b) {
	if (a.x != b.x) return a.x < b.x;
	return a.y < b.y;
}

void solve () {
	int ans = INF, ansC, ansH;

	sort (c, c + cntC, cmp);
	sort (h, h + cntH, cmp);

	for (int i = 0; i < cntH; i++) {
		for (int j = 0; j < cntC; j++) {
			int d = Count(i, j);
			if (d < ans) {
				ans = d;
				ansH = i;
				ansC = j;
			}
		}
	}
	printf("%d %d %d %d\n", h[ansH].x, h[ansH].y, c[ansC].x, c[ansC].y);
}

int main () {
	while (scanf("%d%d", &n, &m) == 2 && n && m) {
		init ();
		solve ();
	}
	return 0;
}
