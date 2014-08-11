#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

int N, M, P, K;

inline double getp (double n, double x) {
	double s = n * n;
	double t = 2 * (n - x + 1) * x - 1;
	return t / s;
}

inline double handle (double p) {
	return (1 - pow(1 - 2 * p, K)) / 2;
}

double solve () {
	double ret = 0;
	for (int x = 1; x <= N; x++) {
		double px = getp(N, x);
		for (int y = 1; y <= M; y++) {
			double py = getp(M, y);
			for (int z = 1; z <= P; z++) {
				double pz = getp(P, z);
				ret += handle(px * py * pz);
			}
		}
	}
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%d%d%d%d", &N, &M, &P, &K);
		printf("Case %d: %.10lf\n", kcas, solve());
	}
	return 0;
}
