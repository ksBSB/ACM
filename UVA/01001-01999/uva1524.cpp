#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using  namespace std;
const int maxn = 1005;

int N;
double s, e, a[maxn];

double f (double x) {
	double ret = 0;
	for (int i = 0; i <= N; i++)
		ret += a[i] * pow(x, i+1);
	return ret;
}

int main () {
	while (scanf("%d", &N) == 1 && N) {
		for (int i = N; i >= 0; i--) {
			scanf("%lf", &a[i]);
			a[i] /= (i+1);
		}
		scanf("%lf%lf", &s, &e);
		printf("%.3lf\n", (f(e) - f(s)) / (e - s));
	}
	return 0;
}
