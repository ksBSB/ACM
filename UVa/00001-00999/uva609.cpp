#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;
const int N = 10;
const double INF = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-9;

struct Point {
	double x, y;
	Point () { };
	Point (double x, double y) {
		this->x = x; this->y = y;
	}
}p[N];

struct Line {
	int id;
	double A, B, C;
	Point p1, p2;
	void set(Point a, Point b) {
		p1 = a; p2 = b;
		A = p2.y - p1.y;
		B = p1.x - p2.x;
		C = -(B * p1.y + A * p1.x);
	}
}line[N];

int n;
double r, l;
vector<Line> g;

bool cmp(Line a, Line b) {
	return a.id < b.id;
}

double distant (double x, double y) {
	return sqrt(x * x + y * y);
}

void init () {
	scanf("%lf%lf%d", &r, &l, &n);
	for (int i = 0; i < n; i++)
		scanf("%lf%lf", &p[i].x, &p[i].y);

	for (int i = 0; i < n; i++) {
		line[i].set(p[i], p[(i+1)%n]);
		line[i].id = i;
	}
}

inline bool judge (Point a, Point b, Point c, Point d) {
	int xup, xdown, yup, ydown;
	xup = xdown = yup = ydown = 0;
	
	double Max = max(c.x, d.x), Min = min(c.x, d.x);
	if (a.x - Max > -eps || b.x - Max > -eps) xup = 1;
	if (a.x - Min < eps || b.x - Min < eps) xdown = 1;

	Max = max(c.y, d.y); Min = min(c.y, d.y);
	if (a.y - Max > -eps || b.y - Max > -eps) yup = 1;
	if (a.y - Min < eps || b.y - Min < eps) ydown = 1;

	return xup + xdown + yup + ydown == 4;
}

inline Point find (Line a, Line b) {
	double x = (a.B * b.C - b.B * a.C) / (a.A * b.B - a.B * b.A);
	double y = (a.A * b.C - b.A * a.C) / (b.A * a.B - a.A * b.B);
	return Point(x, y);
}

inline double cat (int u) {
	Point v[20];
	int cnt = 0;

	for (int i = 0; i < g.size(); i++) {
		double Ai = g[i].A * line[u].B;
		double Bi = g[i].B * line[u].A;
		if (fabs(Ai - Bi) < eps) continue;

		Point k = find(g[i], line[u]);
		v[cnt++] = k;
	}

	double ans = INF;
	for (int i = 0; i < cnt; i++) {
		for (int j = i+1; j < cnt; j++) if (judge(v[i], v[j], line[u].p1, line[u].p2)) {
			double dis = distant(v[i].x - v[j].x, v[i].y - v[j].y);
			ans = min(ans, dis);
		}
	}
	return ans;
}

double del () {
	g.clear();
	Line t;
	t.set(Point(0, 0), Point(r, 0));
	g.push_back(t);
	t.set(Point(0, 0), Point(0, l));
	g.push_back(t);
	t.set(Point(r, l), Point(r, 0));
	g.push_back(t);
	t.set(Point(r, l), Point(0, l));
	g.push_back(t);

	double len = 0;
	for (int i = 0; i < n; i++) {
		len += cat(i);
		g.push_back(line[i]);
	}
	return len;
}

double solve () {
	double ans = INF;
	sort(line, line + n, cmp);
	do {
		ans = min(ans, del());
	} while (next_permutation(line, line + n, cmp));

	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init ();

		printf("Minimum total length = %.3lf\n", solve () );

		if (cas) printf("\n");
	}
	return 0;
}
