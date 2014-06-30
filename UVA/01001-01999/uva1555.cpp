#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int N = 1005;
int n;
double a, k[N], b[N];

double solve() {
	double ans = 0;
	k[1] = 0; b[1] = a;
	k[2] = 1; b[2] = 0;
	for (int i = 3; i <= n; i++) {
		k[i] = 2 * k[i-1] - k[i-2];
		b[i] = 2 * b[i-1] - b[i-2] + 2;
		if (ans * k[i] + b[i] < 0) ans = -b[i]/k[i];
	}
	return k[n] * ans + b[n];
}

int main() {
	while (scanf("%d%lf", &n, &a) == 2) {
		printf("%.2lf\n", solve());
	}
	return 0;
}
