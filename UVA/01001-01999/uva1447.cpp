#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const double eps = 1e-9;
const double pi = 4 * atan(1.0);

struct Point {
	double x, y;
	void read() { scanf("%lf%lf", &x, &y); }
	void write() { printf("%lf %lf\n", x, y); }
}A, B, C;

double distance(Point a, Point b) {
	double x = a.x - b.x;
	double y = a.y - b.y;
	return sqrt(x * x + y * y);
}

double getAngle(double a, double b, double c) {
	return acos( (a * a + b * b - c * c) / (2 * a * b) );
}

double getArea(double a, double b, double c) {
	double s =(a + b + c) / 2;
	return sqrt(s * (s - a) * (s - b) * (s - c));
}

double solve (double a, double b, double c) {
	return 2 * getArea(a, b, c) / (a + b + c);
}

int main () {
	while (true) {
		A.read(), B.read(), C.read();
		if (fabs(A.x) < eps && fabs(A.y) < eps && fabs(B.x) < eps && fabs(B.y) < eps && fabs(C.x) < eps && fabs(C.y) < eps)
			break;

		double AB = distance(A, B);
		double BC = distance(B, C);
		double CA = distance(C, A);

		double corA = getAngle(AB, CA, BC) / 2;
		double corB = getAngle(AB, BC, CA) / 2;
		double corC = getAngle(CA, BC, AB) / 2;

		double l = 0, r = min(AB * tan(corB), BC * tan(corB)), a, b;

		while (r - l > eps) {
			double mid = (r + l) / 2;
			a = sqrt(mid + (AB - mid / tan(corB)) / tan(corA)) - sqrt(mid);
			b = sqrt(mid + (BC - mid / tan(corB)) / tan(corC)) - sqrt(mid);  
			double tmp = a * a * tan(corA) + b * b * tan(corC) + 2 * a * b * tan(corA) * tan(corC);
			if (tmp < CA)
				r = mid;
			else
				l = mid;
		}
		double r2 = l;
		double r1 = a * a * tan(corA) * tan(corA);
		double r3 = b * b * tan(corC) * tan(corC);
		printf("%lf %lf %lf\n", r1, r2, r3);

	}
	return 0;
}
