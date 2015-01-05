#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 4;
const double eps = 1e-6;
const char T[6][30] = {"Square", "Rectangle", "Rhombus", "Parallelogram", "Trapezium", "Ordinary Quadrilateral"};

struct Point {
	double x, y;
	void input() { scanf("%lf%lf", &x, &y); }
	friend bool operator < (const Point& a, const Point& b) {
		if (a.x != b.x)
			return a.x < b.x;
		return a.y < b.y;
	}
}p[maxn];

struct Line {
	double A, B, C;
};

inline double distant(Point a, Point b) {
	double x = a.x - b.x;
	double y = a.y - b.y;
	return sqrt(x * x + y * y);
}

Line getLine (Point a, Point b) {
	double A = b.y - a.y;
	double B = a.x - b.x;
	double C = a.y * b.x - a.x * b.y;
	return (Line){A, B, C};
}

bool parallel(Line a, Line b) {
	double A = a.A * b.B;
	double B = a.B * b.A;
	return fabs(A - B) < eps;
}

bool vertical(Line a, Line b) {
	double A = a.A * b.A;
	double B = a.B * b.B;
	return fabs(A + B) < eps;
}


int solve () {
	bool a = parallel(getLine(p[0], p[1]), getLine(p[2], p[3]));
	bool b = parallel(getLine(p[0], p[3]), getLine(p[1], p[2]));

	if (a && b) {
		bool flag = vertical(getLine(p[0], p[1]), getLine(p[1], p[2]));
		double c = distant(p[0], p[1]);
		double d = distant(p[0], p[3]);
		if (fabs(c - d) < eps)
			return flag ? 0 : 2;
		else
			return flag ? 1 : 3;

	} else if (a || b)
		return 4;
	return 5;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		for (int i = 0; i < maxn; i++)
			p[i].input();
		int ans = 5;
		do {
			ans = min(ans, solve());
		} while (next_permutation(p, p + maxn));
		printf("Case %d: %s\n", kcas, T[ans]);
	}
	return 0;
}
