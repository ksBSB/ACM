#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

const int N = 1005;
const double eps = 1e-9;

struct point {
	double x, y;
	void get() {	scanf("%lf%lf", &x, &y); }
	void set(double a, double b) { x = a, y = b; }
	bool operator == (const point& c) {
		return fabs(x - c.x) < eps && fabs(y - c.y) < eps;
	}
}p[N];

int n, vis[N];

void init() {
	scanf("%d", &n);
	p[0].get();
	int t;

	for (int i = 1; i < n; i++) {
		t = i * 2;
		p[t].get();
		p[t - 1].set((p[t - 2].x + p[t].x) / 2, (p[t - 2].y + p[t].y) / 2);
	}
	t = (n - 1) * 2;
	p[t + 1].set((p[t].x + p[0].x) / 2, (p[t].y + p[0].y) / 2);
}

void findLine(double& A, double& B, double& C, const point& u, const point& v) {
	A = v.y - u.y;
	B = u.x - v.x;
	C = u.y * (v.x - u.x) + (u.y - v.y) * u.x;
}

point findPoint(double A, double B, double C, point k) {

	point c;
	c.x = ( (B * B - A * A) * k.x - 2 * A * B * k.y - 2 * A * C ) / (A * A + B * B);
	c.y = (-2 * A * B * k.x + (A * A - B * B)* k.y - 2 * B * C) / (A * A + B * B);
	return c;
}

bool search(point k) {
	for (int i = 0; i < n; i++) {

		if (vis[i * 2]) continue;

		if (p[i * 2] == k) {
			vis[i * 2] = 1;
			return true;
		}
	}
	return false;
}

bool judge(double A, double B, double C) {

	for (int i = 0; i < n; i++) {

		if (vis[i * 2]) continue;

		point k = findPoint(A, B, C, p[i * 2]);
		
		if (!search(k)) return false;
	}
	return true;
}

bool solve() {
	double A, B, C;
	for (int i = 0; i < n; i++) {
		findLine(A, B, C, p[i], p[i + n]);

		memset(vis, 0, sizeof(vis));
		vis[i] = vis[i + n] = 1;

		if (judge(A, B, C) ) return true;
	}
	return false;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		init();
		printf("Case %d: %s\n", i, solve() ? "YES" : "NO");	
	}
	return 0;
}
