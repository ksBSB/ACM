#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;
struct point {
	int x, y;
	point() {}

	point(int x, int y) { 
		this->x = x;
		this->y = y;
	}

	point operator - (const point& c) {
		return point(x-c.x, y-c.y);
	}
};

point pos (int n) {
	if (n == 1) return point(0, 0);
	int r;	

	for (r = 1, n--; n > r * 6; r++)
		n -= r * 6;

	if (n <= r) return point(r-n, -n);
	if (n <= 2*r) return point(r-n, -r);
	if (n <= 3*r) return point(-r, n-3*r);
	if (n <= 4*r) return point(n-4*r, n-3*r);
	if (n <= 5*r) return point(n-4*r, r);
	return point(r, 6*r-n);
}

int solve (int n, int m) {
	point d = pos(n) - pos(m);

	if (d.x * d.y >= 0)
		return max(abs(d.x), abs(d.y));
	else
		return abs(d.x) + abs(d.y);
}

int main () {
	int n, m;
	while (scanf("%d%d", &n, &m) == 2 && n + m) {
		printf("The distance between cells %d and %d is %d.\n", n, m, solve(n, m));
	}
	return 0;
}
