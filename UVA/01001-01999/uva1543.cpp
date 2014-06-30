#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int N = 50;
const double pi = atan(1.0) * 4;

int n, k;
double dp[N][N][N];
double p[N], d[N][N], area[N][N][N];

inline double dis(int x, int y) {
	double a = p[y] - p[x];

	if (a > 0.5)
		a = 1 - a;
	return 2 * sin(a*pi);
}

inline double getArea(double x, double y, double z) {
	double tmp = (x + y + z)/2;
	return sqrt(tmp * (tmp - x) * (tmp - y) * (tmp - z));
}

void init () {
	for (int i = 0; i < n; i++)
		scanf("%lf", &p[i]);

	for (int i = 0; i < n; i++)
		for (int j = i+1; j < n; j++)
			d[i][j] = d[j][i] = dis(i, j);

	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			for (int t = j+1; t < n; t++) {
				double tmp = getArea(d[i][j], d[j][t], d[t][i]);
				area[i][j][t] = area[i][t][j] = tmp;
				area[j][i][t] = area[j][t][i] = tmp;
				area[t][i][j] = area[t][j][i] = tmp;
			}
		}
	}
}

double solve () {
	memset(dp, 0, sizeof(dp));

	for (int i = 3; i <= k; i++) {
		for (int x = 0; x < n; x++) {
			for (int y = x+1; y < n; y++) {

				for (int z = y+1; z < n; z++)
					dp[x][z][i] = max(dp[x][z][i], dp[x][y][i-1] + area[x][y][z]);
			}
		}
	}

	double ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			ans = max(ans, dp[i][j][k]);
		}
	}
	return ans;
}

int main () {
	while (scanf("%d%d", &n, &k) == 2 && n + k) {
		init ();
		printf("%.6lf\n", solve());
	}
	return 0;
}
