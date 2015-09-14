#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const double pi = 4 * atan(1.0);

int A, B, C;

double getAngle(double a, double b, double c) {
	double tmp = (a * a + b * b - c * c) / (2 * a * b);
	return acos(tmp);
}

double getArea(double a, double b, double c) {
	double s =(a + b + c) / 2;
	return sqrt(s * (s - a) * (s - b) * (s - c));
}

int main () {
	int cas = 1;
	while (scanf("%d%d%d", &A, &B, &C) == 3) {
		if (A == 0 || B == 0 || C == 0)
			break;
		double cornerA = getAngle(B, C, A);
		double cornerB = getAngle(A, C, B);
		double cornerC = getAngle(A, B, C);

		double FAB = (pi - cornerA) / 2;
		double FBA = (pi - cornerB) / 2;
		double cornerF = pi - FAB - FBA;

		double EAC = (pi - cornerA) / 2;
		double ECA = (pi - cornerC) / 2;
		double cornerE = pi - EAC - ECA;

		double DBC = (pi - cornerB) / 2;
		double DCB = (pi - cornerC) / 2;
		double cornerD = pi - DBC - DCB;

		double Sabc = getArea(A, B, C);
		double Sabf = getArea(C, C / sin(cornerF) * sin(FAB), C / sin(cornerF) * sin(FBA));
		double Sace = getArea(B, B / sin(cornerE) * sin(EAC), B / sin(cornerE) * sin(ECA));
		double Sbcd = getArea(A, A / sin(cornerD) * sin(DBC), A / sin(cornerD) * sin(DCB));
		double ans1 = Sabc + Sabf + Sace + Sbcd;

		double ans2 = 0;
		double Rf = Sabf * 2 / C;
		ans2 += Rf * Rf * cornerF;
		double Re = Sace * 2 / B;
		ans2 += Re * Re * cornerE;
		double Rd = Sbcd * 2 / A;
		ans2 += Rd * Rd * cornerD;

		printf("Case %d: %.2lf %.2lf\n", cas++, ans1, ans2 / 2);
	}
	return 0;
}
