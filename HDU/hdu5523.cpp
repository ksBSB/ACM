#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;
int n, s, t;

int solve () {
	if (n <= 2) return 0;
	if ((s == 1 || s == n) && (t == 1 || t == n)) return 0;
	if (s == 1 || s == n) return 1;

	if (s == t + 1 || s == t - 1) return 1;
	return 2;
}

int main () {
	while (scanf("%d%d%d", &n, &s, &t) == 3) {
		if (n != 1 && s == t) printf("-1\n");
		else printf("%d\n", solve());
	}

	return 0;
}
