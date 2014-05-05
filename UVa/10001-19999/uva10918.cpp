#include <stdio.h>
#include <string.h>
#define ll long long

ll n, c[35];

void init() {
	memset(c, 0, sizeof(c));
	c[0] = 1;
	c[2] = 3;
	for (int i = 4; i <= 30; i++)
		c[i] = 4 * c[i - 2] - c[i - 4];
}

int main() {
	init();
	while (scanf("%lld", &n), n!= -1) {
		printf("%lld\n", c[n]);
	}
	return 0;
}
