#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 10;

int N;
double a[maxn];

void div (double* f, double x, int n) {
	f[n+1] = 0;
	for (int i = n; i >= 0; i--)
		f[i] += f[i+1] * x;

	for (int i = 0; i < n; i++)
		f[i] = f[i+1];
}

double func (double* f, double x, int n) {
	double ret = 0, u = 1;
	for (int i = 0; i <= n; i++) {
		ret += f[i] * u;
		u *= x;
	}
	return ret;
}

double newton (double* f, int n) {
	double fd[maxn];
	for (int i = 0; i < n; i++)
		fd[i] = f[i+1] * (i+1);
	double x = -100;
	for (int i = 0; i < 100; i++)
		x -= func(f, x, n) / func(fd, x, n-1);
	return x;
}

void solve () {
	for (int i = 0; i < N; i++) {
		double x = newton(a, N-i);
		printf(" %.4lf", x);
		div(a, x, N-i);
	}
}

int main () {
	int cas = 1;
	while (scanf("%d", &N) == 1 && N) {
		for (int i = N; i >= 0; i--)
			scanf("%lf", &a[i]);
		printf("Equation %d:", cas++);
		solve();
		printf("\n");
	}
	return 0;
}
