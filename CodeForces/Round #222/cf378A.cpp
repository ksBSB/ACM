#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
	int a, b;
	int x = 0, y = 0, z = 0;
	scanf("%d%d", &a, &b);
	for (int i = 1; i <= 6; i++) {
		if (abs(i - a) > abs(i - b)) z++;
		else if (abs(i - a) == abs(i - b)) y++;
		else x++;
	}
	printf("%d %d %d\n", x, y, z);
	return 0;
}
