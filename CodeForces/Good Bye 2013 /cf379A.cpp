#include <stdio.h>
#include <string.h>

int main() {
	int ans = 0, a, b;
	scanf("%d%d", &a, &b);
	while (a >= b) {
		ans += (a / b) * b;
		a = a / b + a % b;
	}
	printf("%d\n", ans + a);
	return 0;
}
