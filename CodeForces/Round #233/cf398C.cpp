#include <stdio.h>
#include <string.h>

int main () {
	int n;
	scanf("%d", &n);
	if (n == 5) {
		printf("1 2 3\n1 3 3\n2 4 2\n4 5 1\n");
		printf("3 4\n3 5\n");
	} else {
		int t = n/2;
		for (int i = 1; i <= t; i++) printf("%d %d %d\n", i, i + t, 1);
		for (int i = 1; i+t < n; i++) printf("%d %d %d\n", i+t, i+t+1, 2*i-1);
		for (int i = 1; i < t; i++) printf("%d %d\n", i, i+1);
		printf("1 3\n");
	}

	return 0;
}
