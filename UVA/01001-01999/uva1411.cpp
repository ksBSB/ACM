#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 105;
const double eps = 1e-9;

struct Point {
	double x, y;
	void read() { scanf("%lf%lf", &x, &y); }
}A[maxn], B[maxn];

int n, L[maxn];
double Lx[maxn], Ly[maxn], W[maxn][maxn];
bool S[maxn], T[maxn];

int dcmp(double x) {
	if (fabs(x) < eps) return 0;
	return x < 0 ? -1 : 1;
}

double distance(double x, double y) { return sqrt(x * x + y * y); }

bool match(int i) {
	S[i] = true;
	for (int j = 1; j <= n; j++) {
		if (dcmp(Lx[i] + Ly[j] -  W[i][j]) == 0 && !T[j]) {
			T[j] = true;
			if (!L[j] || match(L[j])) {
				L[j] = i;
				return true;
			}
		}
	}
	return false;
}

void update () {
	double a = 1e20;
	for (int i = 1; i <= n; i++) if (S[i]) {
		for (int j = 1; j <= n; j++) if (!T[j])
			a = min(a, Lx[i]+Ly[j]-W[i][j]);
	}
	for (int i = 1; i <= n; i++) {
		if (S[i]) Lx[i] -= a;
		if (T[i]) Ly[i] += a;
	}
}

void KM () {
	for (int i = 1; i <= n; i++) {
		L[i] = Lx[i] = Ly[i] = 0;
		for (int j = 1; j <= n; j++)
			Lx[i] = max(Lx[i], W[i][j]);
	}
	for (int i = 1; i <= n; i++) {
		while (true) {
			for (int j = 1; j <= n; j++) S[j] = T[j] = 0;
			if (match(i)) break;
			else update();
		}
	}
}

void init () {
	for (int i = 1; i <= n; i++) A[i].read();
	for (int i = 1; i <= n; i++) B[i].read();

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			W[j][i] = -distance(A[i].x - B[j].x, A[i].y - B[j].y);
		}
	}

	KM();
}

int main () {
	int cas = 0;
	while (scanf("%d", &n) == 1) {
		if (cas++) printf("\n");
		init();
		for (int i = 1; i <= n; i++)
			printf("%d\n", L[i]);
	}
	return 0;
}
