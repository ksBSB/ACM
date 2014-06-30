#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 105;
const double eps = 1e-9;

int n, c, rec[N];
double s, p[N];

double solve (int x) {
	double ans = s * p[x];
	double tmp = s * (1-p[x]);

	for (int i = 0; i < c; i++)
		ans += tmp / (1-p[rec[i]]) * p[rec[i]];
	return ans;
}

int main () {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%lf", &p[i]);

	sort (p, p + n);

	c = 0;
	double ans = p[n-1];
	s = 1 - p[n-1];
	rec[c++] = n-1;
	
	for (int i = n-2; i >= 0; i--) {
		double tmp = solve(i);

		if (tmp > ans) {
			ans = tmp;
			rec[c++] = i;
			s *= (1 - p[i]);
		}
	}

	printf("%.12lf\n", ans);
	return 0;
}
