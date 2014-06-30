#include <stdio.h>
#include <string.h>
#include <math.h>

const int N = 50;
struct point {
	int x, y;
	void get() { scanf("%d%d", &x, &y); }
}p[N];
int n;

void init() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) { p[i].get(); }
}

double area(point a, point b, point c) {
	return a.x * b.y + c.x * a.y + b.x * c.y - c.x * b.y - a.x * c.y - b.x * a.y;
}

bool OK(point a, point b, point c, point d) {
	double sum = fabs(area(a, b, d)) + fabs(area(a, c, d)) + fabs(area(b, c, d));
	double tmp = fabs(area(a, b, c));
	if (fabs(sum - tmp) < 1e-9) return true;
	return false;
}

bool judge(point a, point b, point c, point d) {
	if (OK(a, b, c, d)) return false;
	if (OK(a, b, d, c)) return false;
	if (OK(a, c, d, b)) return false;
	if (OK(b, c, d, a)) return false;
	return true;
}

int solve() {
	int ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			for (int x = j + 1; x < n; x++) {
				for (int y = x + 1; y < n; y++) {
					if (judge(p[i], p[j], p[x], p[y])) ans++;
				}
			}
		}
	}
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		init();
		printf("Case %d: %d\n", i, solve());
	}
	return 0;
}
