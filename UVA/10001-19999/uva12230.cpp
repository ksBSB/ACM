#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main () {
	int cas = 1;
	int N;
	double D, p, l, v;

	while (scanf("%d%lf", &N, &D) == 2 && (N || D)) {

		for (int i = 0; i < N; i++) {
			scanf("%lf%lf%lf", &p, &l, &v);
			D = D - l + 2 * l / v;
		}

		printf("Case %d: %.3lf\n\n", cas++, D);
 	}
	return 0;
}
