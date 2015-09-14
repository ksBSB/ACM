#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const int maxn = 105;
const double pi = 4 * atan(1.0);
const double R = 20000 / pi;
const double eps = 1e-9;

struct Point {
	double x, y, z;
	Point (double x = 0, double y = 0, double z = 0): x(x), y(y), z(z) {}
	void read() { scanf("%lf%lf%lf", &x, &y, &z); }
	double pDis() { return x * x + y * y + z * z; }
	Point operator - (const Point& u) { return Point(x-u.x, y-u.y, z-u.z); }
};

int dcmp(double k) {
	if (fabs(k) < eps) return 0;
	return k < 0 ? -1 : 1;
}

int N, M;
Point P[maxn], Q;

int main () {
	while (scanf("%d%d", &N, &M) == 2 && N + M) {
		for (int i = 0; i < N; i++) P[i].read();

		int ans = 0;
		for (int i = 0; i < M; i++) {
			bool flag = false;
			Q.read();
			for (int j = 0; j < N; j++) {
				if (dcmp(P[j].pDis() - R * R - (P[j]-Q).pDis()) >= 0) {
					flag = true; break;
				}
			}
			if (flag) ans++;
		}

		printf("%d\n", ans);
	}
	return 0;
}
