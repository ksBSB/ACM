#include <stdio.h>
#include <string.h>

int main() {
	int h, m, hh, mm;
	scanf("%d:%d", &h, &m);
	scanf("%d:%d", &hh, &mm);
	int x, y;
	if (mm > m) {
		h--, m += 60;
	}
	y = m - mm;
	x = (h + 24 - hh) % 24;
	printf("%02d:%02d\n", x, y);
	return 0;
}
