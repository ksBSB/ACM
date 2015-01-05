#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>

using namespace std;

const int maxn = 3;

struct point {
	double x, y;
	void input() { 
		scanf("%lf%lf", &x, &y);
	}
}p[maxn], m[maxn];

struct line {
	double A, B, C;
}l[maxn];

point getPoint(point a, point b) {
	double x = a.x + (b.x - a.x) * 2 / 3;
	double y = a.y + (b.y - a.y) * 2 / 3;	
	return (point){x, y};
}

line getLine (point a, point b) {
	double A = b.y - a.y;
	double B = a.x - b.x;
	double C = a.y * b.x - a.x * b.y;
	return (line){A, B, C};
}

point getCpoint(line a, line b) {
	double x = (a.B * b.C - a.C * b.B) / (a.A * b.B - b.A * a.B);
	double y = (b.C * a.A - a.C * b.A) / (a.B * b.A - a.A * b.B);
	return (point){x, y};
}

double area(point a, point b, point c) {
	double A = a.x * b.y - b.x * a.y;
	double B = b.x * c.y - c.x * b.y;
	double C = c.x * a.y - a.x * c.y;
	return fabs((A + B + C) / 2);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		for (int i = 0; i < maxn; i++)
			p[i].input();

		for (int i = 0; i < maxn; i++)
			m[i] = getPoint(p[i], p[(i+1) % maxn]);

		for (int i = 0; i < maxn; i++)
			l[i] = getLine(p[i], m[(i+1) % maxn]);

		for (int i = 0; i < maxn; i++)
			p[i] = getCpoint(l[i], l[(i+1) % maxn]);
		printf("%.0lf\n", area(p[0], p[1], p[2]));
	}
	return 0;
}
