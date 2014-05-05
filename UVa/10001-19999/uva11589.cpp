#include <stdio.h>
#include <string.h>
#include <algorithm>

#define div(i, a, b, c, d) { a = i&1; b = (i>>1)&1; c = (i>>2)&1; d = (i>>3); }
#define judge(a, b, c, d)  ((a+b+c+d)%2 == 1 ? 1 : -1) 

using namespace std;
const int N = 20;

int n, X, Y, Z, Q;
int s[N][N][N][N*5];

inline int cat (char* str) {
	int h, m;
	sscanf(str, "%d:%d", &h, &m);
	return h * 4 + m / 15;
}

inline void init () {

	memset(s, 0, sizeof(s));
	scanf("%d%d%d%d", &X, &Y, &Z, &Q);

	char str1[N], str2[N];
	int x1, y1, z1, t1, x2, y2, z2, t2;

	for (int i = 0; i < n; i++) {
		scanf("%d%d%d%d%d%d%s%s", &x1, &y1, &z1, &x2, &y2, &z2, str1, str2);
		t1 = cat(str1); t2 = cat(str2);

		for (int a = x1+1; a <= x2; a++)
			for (int b = y1+1; b <= y2; b++)
				for (int c = z1+1; c <= z2; c++)
					for (int d = t1+1; d <= t2; d++)
						s[a][b][c][d] = 1;
	}

	for (int a = 1; a <= X; a++) {
		for (int b = 1; b <= Y; b++) {
			for (int c = 1; c <= Z; c++) {
				for (int d = 1; d <= 96; d++) {
					for (int i = 1; i < 16; i++) {
						int xi, yi, zi, ti;
						div(i, xi, yi, zi, ti);
						s[a][b][c][d] += s[a-xi][b-yi][c-zi][d-ti] * judge(xi, yi, zi, ti);
					}
				}
			}
		}
	}
}

inline void solve () {
	char str[N];
	int x, y, z, t;
	
	scanf("%d%d%d%s", &x, &y, &z, str);
	t = cat(str);

	int ans = 0;
	for (int a = 1; a <= X-x+1; a++) {
		for (int b = 1; b <= Y-y+1; b++) {
			for (int c = 1; c <= Z-z+1; c++) {
				for (int d = 1; d <= 96-t+1; d++) {
					int v = 0, xi, yi, zi, ti;
					for (int i = 0; i < 16; i++) {
						div(i, xi, yi, zi, ti);
						v -= s[a-1+xi*x][b-1+yi*y][c-1+zi*z][d-1+ti*t] * judge(xi, yi, zi, ti);
					}

					if (!v) ans++;
				}
			}
		}
	}

	if (ans) printf("%d safe place(s) found\n", ans);
	else printf("No safe place(s) found\n");
}

int main () {
	int cas = 1;
	while (scanf("%d", &n), n) {
		init ();
		printf("3D World %d:\n", cas++);
		while (Q--) {
			solve ();
		}
	}
	return 0;
}
