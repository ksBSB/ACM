#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		int n;
		double p, s = 0;
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%lf", &p);
			s += p;
		}

		for (int i = 0; i < n; i++)
			scanf("%lf", &p);
		printf("Case #%d: %.6lf\n", kcas, (n + 1) / s);
	}
	return 0;
}
