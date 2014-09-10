#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const char sign[8][10] = {"a", "ab", "aab", "aabb", "aaaba", "aaabab", "aaababb", "aaababbb"};
const char str[10] = "aababb";

int main () {
	int cas, n, m;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%d%d", &m, &n);
		printf("Case #%d: ", kcas);
		if (m == 1) { 

			for (int i = 0; i < n; i++)
				printf("a");

		} else if (m > 2) {

			for (int i = 0; i < n; i++)
				printf("%c", 'a' + i % 3);

		} else if (n <= 8) {
			printf("%s", sign[n-1]);
		} else {
			n -= 2;
			printf("aa");
			int k = n / 6, t = n % 6;
			for (int i = 0; i < k; i++)
				printf("%s", str);

			if (t <= 4) {
				for (int i = 0; i < t; i++)
					printf("a");
			} else {
				for (int i = 0; i < t; i++)
					printf("%c", str[i]);
			}
		}
		printf("\n");
	}
	return 0;
}
