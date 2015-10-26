#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		double x, l = 0, r = 0.5;
		scanf("%lf", &x);
		for (int i = 1; i <= 1000; i++) {
			if (x == l || x == r) {
				printf("-1\n");
				break;
			}
			l = (l + r) / 2;
			if (x < l) {
				printf("%d\n", i * 4);
				break;
			}
		}
	}
	return 0;
}
