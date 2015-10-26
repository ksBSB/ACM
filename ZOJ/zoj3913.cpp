#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 5;
const double eps = 1e-8;
const double pi = 4 * atan(1);

inline int dcmp(double x) {
	if (fabs(x) < eps) return 0;
	return x < 0 ? -1 : 1;
}

struct Rectangle {
	double z, w, l, h;
	void read () { scanf("%lf%lf%lf%lf", &z, &w, &l, &h); }
	double volume () { return w * l * h; }
	double contain(double H) {
		double dn = z-h/2, up = min(z+h/2, H);
		return w * l * max(0.0, up-dn);
	}
}R[maxn];

struct Circle {
	double z, r;
	void read () { scanf("%lf%lf", &z, &r); }
	double volume () { return pow(r, 3) * pi * 4 / 3; }
	double lost(double H) { return pi * H * H * (r - H / 3); }
	double contain(double H) {
		if (dcmp(H-(z+r)) >= 0) return volume();
		if (dcmp(H-(z-r)) <= 0) return 0;

		if (dcmp(H-z) >= 0) return volume()-lost(z+r-H);
		else return lost(H-(z-r));
	}
}C[maxn];

int M, N;
double W, L, V;

double getVolume(double H) {
	double ret = H * W * L;
	for (int i = 0; i < M; i++)
		ret -= R[i].contain(H);
	for (int i = 0; i < N; i++)
		ret -= C[i].contain(H);
	return ret;
}

double solve () {
	double l = 0, r = V / (W*L);
	for (int i = 0; i < M; i++) r += R[i].volume()/(W*L);
	for (int i = 0; i < N; i++) r += C[i].volume()/(W*L);
	//while (r-l > 1e-4) {
	for (int i = 0; i < 200; i++) {
		double mid = (l + r) / 2;
		double vol = getVolume(mid);
		if (dcmp(vol-V) > 0) r = mid;
		else l = mid;
	}
	return l;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%lf%lf%lf%d%d", &W, &L, &V, &M, &N);
		for (int i = 0; i < M; i++) R[i].read();
		for (int i = 0; i < N; i++) C[i].read();
		printf("%.6lf\n", solve());
	}
	return 0;
}
