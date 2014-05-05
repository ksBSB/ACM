#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>

using namespace std;

const int N = 10;
const double INF = 0x3f3f3f3f;

int p[N];

bool init() {
	int sum = 0;
	for (int i = 0; i < 8; i++) {
		scanf("%d", &p[i]);
		sum += p[i];
	}
	return sum ? true : false;
}

double sit() {
	double x = p[0] + p[1] + p[2];
	double y = p[5] + p[6] + p[7];
	double k = p[0] + p[3] + p[5];
	double t = p[2] + p[4] + p[7];
	return sqrt(pow(x - y, 2) + pow(k - t, 2));
}

double solve() {
	double ans = INF;
	sort(p, p + 8);
	do {
		ans = min(ans, sit());
	} while (next_permutation(p, p + 8));
	return ans;
}

int main() {
	while (init()) {
		printf("%.3lf\n", solve());
	}
	return 0;
}
