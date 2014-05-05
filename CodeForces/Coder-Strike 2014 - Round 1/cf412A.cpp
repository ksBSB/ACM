#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 105;

int main () {
	int n, k;
	char s[N];
	scanf("%d%d%s", &n, &k, s);

	if (k <= n - k) {
		for (int i = 1; i < k; i++)
			printf("LEFT\n");

		printf("PRINT %c\n", s[0]);
		for (int i = 1; i < n; i++) {
			printf("RIGHT\n");
			printf("PRINT %c\n", s[i]);
		}
	} else {
		for (int i = 0; i < n - k; i++)
			printf("RIGHT\n");
		printf("PRINT %c\n", s[n-1]);

		for (int i = n-2; i >= 0; i--) {
			printf("LEFT\n");
			printf("PRINT %c\n", s[i]);
		}
	}
	return 0;
}
