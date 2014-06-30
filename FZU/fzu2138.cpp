#include <stdio.h>

int main () {
	int cas;	
	scanf("%d", &cas);

	while (cas--) {
		int n, num, sum = 0;

		scanf("%d", &n);
		for (int i = 0; i < 5; i++) {
			scanf("%d", &num);
			sum += num;
		}

		sum = sum - 2 * n;
		if (sum < 0) sum = 0;

		printf("%d\n", sum / 3 + (sum % 3 ? 1 : 0));
	}
	return 0;
}
