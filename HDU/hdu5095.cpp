#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main () {
	int cas, a[20];
	char s[20] = "1pqruvwxyz";
	scanf("%d", &cas);
	while (cas--) {
		for (int i = 1; i <= 10; i++)
			scanf("%d", &a[i]);

		bool flag = true;
		for (int i = 1; i <= 10; i++) {
			if (a[i] == 0) continue;

			if (!flag || a[i] < 0)
				printf("%c", a[i] < 0 ? '-' : '+');

			if (i == 10 || abs(a[i]) != 1)
				printf("%d", abs(a[i]));

			if (i < 10)
				printf("%c", s[i]);
			flag = false;
		}
		if (flag)
			printf("0");
		printf("\n");
	}
	return 0;
}
