#include <cstdio>
#include <cstring>

int s, x, y, dx, dy;

bool judge (int a, int b) {
	return (a%s) && (b%s) && ((a/s+b/s) % 2);
}

int main () {
	while (scanf("%d%d%d%d%d", &s, &x, &y, &dx, &dy) == 5 && s + x + y + dx + dy) {
		int i;
		for (i = 0; i < 2 * s; i++) {
			if (judge (x, y)) {
				printf("After %d jumps the flea lands at (%d, %d).\n", i, x, y);
				break;
			}
			x += dx;
			y += dy;
		}
		if (i == 2 * s)
			printf("The flea cannot escape from black squares.\n");
	}
	return 0;
}
