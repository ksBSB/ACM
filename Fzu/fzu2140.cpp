#include <stdio.h>
#include <math.h>

const int N = 105;
const double tmp = 0.005;
double x[N], y[N];

void init() {
	x[0] = y[0] = 0;
	x[1] = 0, y[1] = 1;
	x[2] = sqrt(double(3)) / 2, y[2] = 1.0 / 2;
	x[3] = x[2] - 1, y[3] = 1.0 / 2;
	for (int i = 4; i < N; i++) {
		x[i] = i * tmp;
		y[i] = sqrt(1 - x[i] * x[i]);
	}
}

int main (){
	init();
	int cas, n;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &n);
		if (n < 4) printf("No\n");
		else {
			printf("Yes\n");
			for (int i = 0; i < n; i++)
				printf("%.6lf %.6lf\n", x[i], y[i]);
		}
	}
	return 0;
}
