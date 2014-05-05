#include <stdio.h>
#include <string.h>
#include <math.h>

const int N = 200;

int n;
double s[N][N], a[N][N], b[N][N];

inline double cal(double x) {
	if (fabs(x) < 1e-9) return 0;
	return x;
}

int main () {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < n; j++) scanf("%lf", &s[i][j]);

	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			a[i][j] = a[j][i] = (s[i][j] + s[j][i]) / 2;
			double t = (s[i][j] - s[j][i]) / 2;
			b[i][j] = t; b[j][i] = -t;
		}
	}
	for (int i = 0; i < n; i++) {
		printf("%.8lf", cal(a[i][0]));
		for (int j = 1; j < n; j++) printf(" %.8lf", cal(a[i][j]));
		printf("\n");
	}

	for (int i = 0; i < n; i++) {
		printf("%.8lf", cal(b[i][0]));
		for (int j = 1; j < n; j++) printf(" %.8lf", cal(b[i][j]));
		printf("\n");
	}
	return 0;
}
