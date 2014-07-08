#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>

using namespace std;
const double sq3 = sqrt(3.0);
const double INF = 0x3f3f3f3f;
const int d[7][2] = { {0, 0}, {0, -2}, {0, 2}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
struct point {
	double x, y;
};
double tx, ty;

double dis(double x, double y) {
	return sqrt(x*x+y*y);
}

point find(double xi, double yi) {
	int cx = (int)(xi/tx);
	int cy = (int)(yi/ty);
	if (cx&1) {
		if (cy%2 == 0) cy++;
	} else {
		if (cy%2) cy++;
	}
	
	point A;
	double tmp = INF;
	for (int i = 0; i < 7; i++) {
		double a = dis((cx+d[i][0])*tx-xi, (cy+d[i][1])*ty-yi);
		if (a < tmp) {
			A.x = (cx+d[i][0])*tx;
			A.y = (cy+d[i][1])*ty;
			tmp = a;
		}
	}
	return A;
}

double solve(point A, point B) {
	int cx = (int)(fabs(A.x-B.x)/tx+0.5);
	int cy = (int)(fabs(A.y-B.y)/ty+0.5);
//	return max(cx, cy) * sq3;
	if (cx > cy)
		return cx * sq3;
	else
		return (cy + (cx - cy) / 2) * sq3;

}

int main () {
	double r, x1, y1, x2, y2;	
	while (scanf("%lf%lf%lf%lf%lf", &r, &x1, &y1, &x2, &y2) == 5 && (r||x1||y1||x2||y2)) {
		tx = 3*r/2; ty = sq3*r/2;
		point A = find(x1, y1);
		point B = find(x2, y2);

		if (fabs(A.x-B.x) < 1e-9 && fabs(A.y-B.y) < 1e-9) {
			printf("%.3lf\n", dis(x1-x2, y1-y2));
		} else {
			double len = dis(A.x-x1, A.y-y1) + dis(B.x-x2, B.y-y2);
			len = len + solve(A, B)*r;
			printf("%.3lf\n", len);
		}
	}
	return 0;
}
