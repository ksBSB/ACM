#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const double pi = 4 * atan(1);
const double eps = 1e-4;

double A[6];

void CornerToCorner () {
	double t = 0;
	for (int i = 1; i < 6; i += 2) {
		if (A[i] < 0) continue; 
		t += A[i];
	}
	for (int i = 1; i < 6; i += 2)
		if (A[i] < 0) A[i] = pi - t;
}
double getAngle(double a, double b, double c) {
	return acos( (a * a + b * b - c * c) / (2 * a * b) );
}

void EdgeToCorner () {
	for (int i = 1; i < 6; i += 2) {
		if (A[i] < 0)
			A[i] = getAngle( A[(i+1)%6], A[(i+3)%6], A[i-1]);
	}
}

double getEdge(double x, double y, double c) {
	//printf("%lf %lf\n", c, cos(c));
	return sqrt(x * x + y * y - 2 * x * y * cos(c));
}

bool judge () {
	for (int i = 0; i < 6; i++)
		if (A[i] < 0)
			return false;
	if (fabs(A[1] + A[3] + A[5] - pi) > eps) {
		return false;
	}

	if (A[0] + A[2] <= A[4] || A[2] + A[4] <= A[0] || A[0] + A[4] <= A[2]) {
		return false;
	}

	/*
	for (int i = 0; i < 6; i += 2)
		printf("%lf\n", A[i] / sin(A[i+1]));
		*/

	for (int i = 0; i < 4; i += 2) {
		//if (fabs(A[i] / sin(A[i+1]) - A[i+2] / sin(A[i+3])) > eps)
		//printf("%lf\n", fabs(A[i] * sin(A[i+3]) - sin(A[i+1]) * A[i+2]));
		if (fabs(A[i] * sin(A[i+3]) - sin(A[i+1]) * A[i+2]) > eps)
			return false;
	}
	return true;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		int S = 0, C = 0, E = 0;
		bool flag = false;
		for (int i = 0; i < 6; i++) {
			scanf("%lf", &A[i]);
			if (A[i] > 0) {
				S++;
				if (i&1) C++;
				else E++;
			}
		}

		if (S < 3) {
			printf("Invalid input.\n");
			continue;
		}

		while (S < 6) {
			int T = S;
			if (C == 2) {
				CornerToCorner();
				S++, C = 3;
			}

			if (E == 3) {
				EdgeToCorner();
				S += 3 - C, C = 3;
			}

			for (int i = 0; i < 6; i += 2) {
				if (A[i] > 0 && A[i+1] > 0) {
					for (int j = 0; j < 6; j += 2) {
						if ((A[j] > 0 && A[j+1] > 0) || (A[j] < 0 && A[j+1] < 0)) continue;

						if (A[j] < 0) {
							A[j] = A[i] / sin(A[i+1]) * sin(A[j+1]);
							//printf("%lf %lf!!!!!\n", A[i] / sin(A[i+1]), A[j] / sin(A[j+1]));
							S++, E++; 
						} else {
							if (A[i+1] < pi / 2 && A[i] < A[j] && A[i] > A[j] * sin(A[i+1]))
								flag = true;
							double tmp = sin(A[i+1]) * A[j] / A[i];
							if (tmp > 1 || tmp < 0)
								continue;
							A[j+1] = asin(sin(A[i+1]) * A[j] / A[i]);
							S++, C++;
						}
					}
				}
			}

			if (E == 2) {
				for (int i = 0; i < 6; i += 2) {
					if (A[i] < 0 && A[i+1] > 0) {
						A[i] = getEdge(A[(i+2)%6], A[(i+4)%6], A[i + 1]);
						S++, E++;
					}
				}
			}
			if (T == S)
				break;
		}

		//printf("%d\n", S);
		/*
		for (int i = 0; i < 6; i++)
			printf("%lf%c", A[i], i == 5 ? '\n' : ' ');
			*/

		if (judge()) {
			if (flag)
				printf("More than one solution.\n");
			else {
				for (int i = 0; i < 6; i++)
					printf("%lf%c", A[i], i == 5 ? '\n' : ' ');
			}
		} else
			printf("Invalid input.\n");

	}
	return 0;
}
