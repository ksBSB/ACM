#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
int t1, t2, s1, s2, w;
double sum;

double solve (int k) {

	double ret = 0;

	if (s2 > t2 + k && s1 > t1 + k) {

		double r = max(t2 + k - s1, 0);
		ret = sum - r * r / 2; 
	} else if (s2 > t2 + k) {

		double r = 2 * s2 - t1 - t2 - 2 * k;
		ret = r * (t2 - t1) / 2;
	} else if (s1 > t1 + k) {

		double r = s2 + s1 - 2 * k - 2 * t1;
		ret = r * (s2 - s1) / 2;
	} else {

		double r = max(s2 - k - t1, 0);
		ret = r * r / 2;
	}

	if (k < 0)
		ret = sum - ret;
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%d%d%d%d%d", &t1, &t2, &s1, &s2, &w);

		sum = 1.0 * (t2 - t1) * (s2 - s1);
		double ans = solve(w) + solve(-w);
		printf("Case #%d: %.8lf\n", kcas, 1 - ans / sum);
	}
	return 0;
}
