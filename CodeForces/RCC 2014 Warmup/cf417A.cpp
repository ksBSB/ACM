#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main () {
	int c, d, n, m, k;
	scanf("%d%d%d%d%d", &c, &d, &n, &m, &k);
	int s = n * m - k;
	int ans = 0;

	if (s <= 0) {
		ans = 0;
	} else {
		int p = d * n;

		int t = s / n;
		int g = s % n;

		ans = t * min(c, p) + min(g * d, c);
	}
	printf("%d\n", ans);
	return 0;
}
