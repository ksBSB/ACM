#include <stdio.h>
#include <string.h>

#define REP(i,n) for (int i = 0; i < (n); i++)
const int N = 15;

int n;
char view[N][N][N], pos[N][N][N];

 char getChar() {
	 char ch;
	 while (true) {
		 ch = getchar();
		 if ((ch >= 'A' && ch <= 'Z') || ch == '.') return ch;
	 }
 }

void input() {
	REP(i, n) REP(k, 6) REP(j, n) view[k][i][j] = getChar();
	REP(x, n) REP(y, n) REP(z, n) pos[x][y][z] = '#';
}

void search(int i, int j, int k, int p, int& x, int& y, int& z) {
	switch(k) {
		case 0:
			x = i, y = j, z = p; return;
		case 1:
			x = i, y = p, z = n - j - 1; return;
		case 2:
			x = i, y = n - j - 1, z = n - p - 1; return;
		case 3:
			x = i, y = n - p - 1, z = j; return;
		case 4:
			x = p, y = j, z = n - i - 1; return;
		case 5:
			x = n - p - 1, y = j, z = i; return;
	}
}

int solve() {

	int x, y, z;

	REP(k, 6) REP(i, n) REP(j, n)
		if (view[k][i][j] == '.')
			REP(p, n) {
				search(i, j, k, p, x, y, z);
				pos[x][y][z] = '.';
			}

	while (true) {
		bool flag = true;
		REP(k, 6) REP(i, n) REP(j, n)
			if (view[k][i][j] != '.')
				REP(p, n) {
					search(i, j, k, p, x, y, z);
					if (pos[x][y][z] == '.') continue;
					if (pos[x][y][z] == '#')
						pos[x][y][z] = view[k][i][j];

					if(pos[x][y][z] == view[k][i][j]) break;
					pos[x][y][z] = '.';
					flag = false;
				}
		if (flag) break;
	}

	int ans = 0;
	REP(x, n) REP(y, n) REP(z, n)
		if (pos[x][y][z] != '.') ans++;
	return ans;
}

int main () {
	while (scanf("%d", &n) == 1 && n) {
		input();
		printf("Maximum weight: %d gram(s)\n", solve() );
	}
	return 0;
}
