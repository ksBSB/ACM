#include <stdio.h>
#include <string.h>

const int N = 105;

int g[N][N];

inline void set (int x, int y) {
	g[x][y] = g[y][x] = 1;
}

void init () {
	memset(g, 0, sizeof(g));

	set(1, 3); set(1, 4); set(2, 100);
	for (int i = 3; i < 60; i += 2) {
		set(i, i+2); set(i, i+3);
		set(i+1, i+2); set(i+1, i+3);
	}

	for (int i = 63; i < 100; i++) set(i, i+1);
}

void solve () {
	int k;
	scanf("%d", &k);

	for (int i = 30; i; i--) if (k >= (1<<i)) {
		k -= (1<<i);
		set(2*i+1, 63+i); set(2*i+2, 63+i);
	}
	if (k) set(1, 63);
}

void put () {
	printf("100\n");
	for (int i = 1; i <= 100; i++) {
		for (int j = 1; j <= 100; j++)
			printf("%c", g[i][j] ? 'Y' : 'N');
		printf("\n");
	}
}

int main () {
	init();
	solve ();
	put();
	return 0;
}
