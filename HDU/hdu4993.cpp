#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		int a, b, c, ans = 0;
		scanf("%d%d%d", &a, &b, &c);

		int p = max(a, b), q = min(a, b);

		do {
			c -= p;
			if (c % q == 0 && c / q >= 1)
				ans++;
		} while (c > 0);

		printf("%d\n", ans);
	}
	return 0;
}