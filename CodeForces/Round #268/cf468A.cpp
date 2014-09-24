#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main () {
	int n;
	scanf("%d", &n);
	if (n < 4)
		printf("NO\n");
	else {
		printf("YES\n");
		if (n&1) {
			printf("4 * 5 = 20\n");
			printf("20 + 3 = 23\n");
			printf("23 + 2 = 25\n");
			printf("25 - 1 = 24\n");

			for (int i = 6; i <= n; i += 2) {
				printf("%d - %d = 1\n", i + 1, i);
				printf("24 * 1 = 24\n");
			}

		} else {
			int c = 1;
			for (int i = 2; i <= 4; i++) {
				printf("%d * %d = %d\n", c, i, c * i);
				c = c * i;
			}

			for (int i = 5; i <= n; i += 2) {
				printf("%d - %d = 1\n", i + 1, i);
				printf("24 * 1 = 24\n");
			}
		}
	}
	return 0;
}
