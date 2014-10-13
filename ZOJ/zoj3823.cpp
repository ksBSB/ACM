#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 550;
const int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

//const int G[5][50] = {{0}, {0}, {3, 4, 2, 1}, {5, 6, 9, 4, 7, 8, 3, 2, 1}};

const int dir_down[4][4][4] = { {{3, 1, 2, 1}, {3, 3, 0, 3}, {1, 3, 0, 3}, {1, 3, 0, 0}},
	{{2, 1, 3, 1}, {2, 1, 3, 3}, {0, 3, 1, 3}, {3, 0, 2, 0}}, 
	{{3, 1, 2, 1}, {1, 3, 0, 3}, {1, 3, 0, 0}} };

const int dir_left[5][4] = { {1, 2, 0, 2}, {1, 2, 0, 2}, {2, 1, 3, 1}, {0, 2, 1, 2}, {0, 2, 1, 1}};
const int dir_up[5][4] = { {2, 0, 3, 0}, {2, 0, 3, 0}, {0, 2, 1, 2}, {3, 0, 2, 0}, {3, 0, 2, 2} };

int L, R, g[maxn][maxn];

void put(int n);

inline void jump(int n, int& x, int& y, int& mv, int len, const int d[4]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 4; j++) {
			g[x][y] = mv;
			mv += len;
			x += dir[d[j]][0];
			y += dir[d[j]][1];
		}
	}
}

inline void moveup(int n, int& x, int& y, int& mv, int len) {
	//printf("moveup:%d\n", len);
	if (n&1) {
		jump(n / 2 - 1, x, y, mv, len, dir_up[0]);
		for (int t = 0; t < 2; t++) {
			g[x][y] = mv;
			x += dir[2][0];
			y += dir[2][1];
			mv += len;
		}
	} else if ((n/2) % 4) {
		jump(n / 2 - 2, x, y, mv, len, dir_up[1]);
		jump(1, x, y, mv, len, dir_up[2]);
	} else {
		jump(n / 2 - 2, x, y, mv, len, dir_up[3]);
		jump(1, x, y, mv, len, dir_up[4]);
	}
}

inline void moveleft(int n, int& x, int& y, int& mv, int len) {
	//printf("moveleft:%d\n", len);
	if (n&1) {
		jump(n / 2, x, y, mv, len, dir_left[0]);
		for (int t = 0; t < 2; t++) { // down twice;
			g[x][y] = mv;
			x += dir[1][0];
			y += dir[1][1];
			mv += len;
		}
	} else if ((n/2) % 4) {
		jump(n / 2 - 1, x, y, mv, len, dir_left[1]);
		jump(1, x, y, mv, len, dir_left[2]);
	} else {
		jump(n / 2 - 1, x, y, mv, len, dir_left[3]);
		jump(1, x, y, mv, len, dir_left[4]);
	}
}

inline void movedown(int n, int& x, int& y, int& mv, int len) {
	int p;

	//printf("movedown!\n");
	if (n&1) {
		for (int k = 0; k < 4; k++) {
			if (k == 0) p = n / 2;
			else if (k == 1 || k == 3) p = 1;
			else p = n / 2 - 2;
			jump(p, x, y, mv, len, dir_down[0][k]);
		}
	} else if ((n/2) % 4 == 1) {
		for (int k = 0; k < 4; k++) {
			if (k == 0) p = n / 2 - 1;
			else if (k == 1 || k == 3) p = (n == 2 && k == 3 ? 0 : 1);
			else p = max(n / 2 - 2, 0);
			jump(p, x, y, mv, len, dir_down[1][k]);
		}
	} else {
		for (int k = 0; k < 3; k++) {
			if (k == 0 || k == 1) p = n / 2 - 1;
			else p = 1;
			jump(p, x, y, mv, len, dir_down[2][k]);
		}
	}
}

void solve (int n, int sx, int sy, int ex, int ey, int flag) {
	if (n <= 1) {
		if (n == 1)
			g[sx][sy] = L;
		return;
	} 

	/*
	printf("%d:\n", n);
	put(10);
	*/

	if (n&1) {
		if ((n/2)&1) {
			if (flag) {
				moveup(n, sx, sy, L, 1);
				moveleft(n, ex, ey, R, -1);
			} else {
				moveup(n, ex, ey, R, -1);
				moveleft(n, sx, sy, L, 1);
			}
			solve(n - 2, sx, sy, ex, ey, flag);
		} else {
			if (flag)
				movedown(n, ex, ey, R, -1);
			else 
				movedown(n, sx, sy, L, 1);
			solve(n - 2, sx, sy, ex, ey, flag^1);
		}
	} else {
		if ((n/2)&1) {
			if (flag)
				movedown(n, ex, ey, R, -1);
			else
				movedown(n, sx, sy, L, 1);
			solve(n - 2, sx, sy, ex, ey, flag^1);
		} else {
			if (flag) {
				moveup(n, sx, sy, L, 1);
				moveleft(n, ex, ey, R, -1);
			} else {
				moveup(n, ex, ey, R, -1);
				moveleft(n, sx, sy, L, 1);
			}
			solve(n - 2, sx, sy, ex, ey, flag);
		}
	}
}

void put (int n) {
	for (int i = 1; i <= n; i++) {
		printf("%d", g[i][1]);
		for (int j = 2; j <= n; j++)
			printf(" %d", g[i][j]);
		printf("\n");
	}
}

int main () {
	int cas, n;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &n);

		int sx, sy, ex, ey, flag;
		L = 1, R = n * n;

		if (n&1) {
			if ((n/2)&1)
				ex = 1, ey = sx = sy = n, flag = 1;
			else
				sx = sy = ex = 1, ey = n, flag = 0;
		} else {
			int t = n / 2;
			t = (t - 1) % 4 + 1;
			if (t == 1)
				sx = 1, sy = ex = 2, ey = n, flag = 0;
			else if (t == 2)
				sx = sy = ey = n, ex = 1, flag = 1;
			else if (t == 3)
				sx = sy = ex = 1, ey = n, flag = 0;
			else
				sx = ey = n, sy = n - 1, ex = 2, flag = 1;
		}

		//printf("%d %d %d %d %d!!!\n", sx, sy, ex, ey, flag);
		solve(n, sx, sy, ex, ey, flag);
		put(n);
	}
	return 0;
}
