#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int N = 50;
const double eps = 1e-9;

int n;
double pos[N];

void init () {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%lf", &pos[i]);
	sort(pos, pos + n);
}

int judge(double a, double d) {

	int p = 0, cnt = 0;
	for (int i = 0; i < n; i++) {
		while (pos[p] < a && p < n)
			p++;

		if (p >= n)
			break;

		if (fabs(pos[p] - a) < eps) {
			cnt++;
			p++;
		}
		a += d;
	}
	return n-cnt;
}

int solve () {

	if (n == 1)
		return 0;

	int ans = (int)n;

	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {

			double dis = pos[j] - pos[i];

			for (int x = 1; x < n; x++) {
				double d = dis / x;
				ans = min(ans, judge(pos[i], d));
			}
		}
	}
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		init ();
		printf("Case #%d: %d\n", i, solve());
	}
	return 0;
}
