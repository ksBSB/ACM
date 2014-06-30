#include <stdio.h>
#include <string.h>
#include <math.h>
const int tmp = -2;

void base() {
	int n, i, num[105];
	memset(num, 0, sizeof(num));
	scanf("%d", &n);
	for (i = 0; n; i++) {
		num[i] = n % tmp;
		n = n / tmp;
		if (num[i] == -1) {
			num[i] = 1, n++;
		}
	}
	while (--i > 0) {
		printf("%d", num[i]);
	}
	printf("%d\n",  num[0]);
}

int main() {
	int cas, ti = 1;
	scanf("%d", &cas);
	while (cas--) {
		printf("Case #%d: ", ti++);
		base();
	}
	return 0;
}
