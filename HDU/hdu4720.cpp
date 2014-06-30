#include <cstdio>
#include <cstring>
#include <cmath>

const double eps = 1e-9;

struct point  {
	double x, y;
}p[3], o, e;

struct line {
	double A, B, C;
}l[3];

inline double dis (double x, double y) {
	return x * x + y * y;
}

line getline (double a, double b, double x, double y) {
	line cur;
	cur.A = a;
	cur.B = b;
	cur.C = -(a*x + b*y);
	return cur;
}

point getP(line a, line b) {
	point cur;
	cur.x = (b.C*a.B - a.C*b.B)/(a.A*b.B - b.A*a.B);
	cur.y = (b.C*a.A - a.C*b.A)/(a.B*b.A - b.B*a.A);
	return cur;
}

void init () {
	for (int i = 0; i < 3; i++)
		scanf("%lf%lf", &p[i].x, &p[i].y);

	for (int i = 0; i < 3; i++)
		l[i] = getline(p[i].x - p[i+1].x, p[i].y - p[i+1].y, (p[i].x+p[i+1].x)/2, (p[i].y+p[i+1].y)/2);
	scanf("%lf%lf", &e.x, &e.y);

	o = getP(l[0], l[1]);
}

bool judge () {
	double r = dis(o.x - p[0].x, o.y - p[0].y);
	point oo;

	double d = dis(o.x - e.x, o.y - e.y);
	if (d > r) 
		return false;

	for (int i = 0; i < 3; i++) {
		int k = (i+1)%3;
		int t = 3 - i - k;

		line a = getline(p[k].y - p[i].y, p[i].x - p[k].x, p[i].x, p[i].y);
		line b = getline(p[i].x - p[k].x, p[i].y - p[k].y, o.x, o.y);
		point cur = getP(a, b);

		oo.x = 2*cur.x - o.x;
		oo.y = 2*cur.y - o.y;

		if (dis(oo.x - p[t].x, oo.y - p[t].y) > r)
			continue;

		if (dis(oo.x - e.x, oo.y - e.y) > r)
			return false;
	}
	return true;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		init ();
		printf("Case #%d: %s\n", i, judge() ? "Danger" : "Safe");
	}
	return 0;
}
