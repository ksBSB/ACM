#include <stdio.h>
#include <string.h>

const int cN[4] = {10, 24, 15, 24};
const int N = 30;

int S[4][N], tB[4][N], tW[4][N];
int cB[4][N], cW[4][N], g[N][N], v[4][N];

void init () {
	for (int i = 0; i < cN[0]; i++)
		S[0][i] = 15;

	for (int i = 0; i < cN[1]; i++) {
		if (i < 10)
			S[1][i] = i + 1;
		else if (i > 13)
			S[1][i] = 24 - i;
		else
			S[1][i] = 10;
	}

	for (int i = 0; i < cN[2]; i++)
		S[2][i] = 10;

	for (int i = 0; i < cN[3]; i++) {
		if (i < 10)
			S[3][i] = i + 1;
		else if (i > 13)
			S[3][i] = 24 - i;
		else
			S[3][i] = 10;
	}
}

void read () {
	memset(g, -1, sizeof(g));
	memset(v, 0, sizeof(v));
	memset(cB, 0, sizeof(cB));
	memset(cW, 0, sizeof(cW));

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < cN[i]; j++) {
			scanf("%d", &tB[i][j]);
			tW[i][j] = S[i][j] - tB[i][j];
		}
	}
}

void cat (int x, int y) {
	if (g[x][y] == 1) {
		cB[0][x]++; cB[1][x+y]++; cB[2][y]++; cB[3][y-x+9]++;
	} else {
		cW[0][x]++; cW[1][x+y]++; cW[2][y]++; cW[3][y-x+9]++;
	}
}

void draw (int x, int y, int val) {
	v[x][y] = 1;

	if (x == 0) {

		for (int i = 0; i < 15; i++) {
			if (g[y][i] == -1) {
				g[y][i] = val;
				cat (y, i);
			}
		}
	} else if (x == 1) {

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 15; j++) {
				if (i + j != y) continue;
				if (g[i][j] == -1) {
					g[i][j] = val;
					cat (i, j);
				}
			}
		}
	} else if (x == 2) {

		for (int i = 0; i < 10; i++) {
			if (g[i][y] == -1) {
				g[i][y] = val;
				cat (i, y);
			}
		}
	} else {

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 15; j++) {
				if (j - i  + 9 != y) continue;
				if (g[i][j] == -1) {
					g[i][j] = val;
					cat (i, j);
				}
			}
		}
	}
}

bool judge () {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < cN[i]; j++) {
			if (v[i][j]) continue;

			if (cW[i][j] == tW[i][j]) {
				draw (i, j, 1);
				return true;
			} else if (cB[i][j] == tB[i][j]) {
				draw (i, j, 0);
				return true;
			}
		}
	}
	return false;
}

void solve () {
	int cnt = 0;
	while (judge()) 
		cnt++;

	if (cnt != 73) memset(g, 0, sizeof(g));

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 15; j++)
			printf("%c", g[i][j] ? '#' : '.');
		printf("\n");
	}
}

int main () {
	init ();

	int cas;
	scanf("%d", &cas);

	while (cas--) {
		read ();
		solve ();
		if (cas) printf("\n");
	}
	return 0;
}
