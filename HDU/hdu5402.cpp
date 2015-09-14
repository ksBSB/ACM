#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 105;
const int dir[2][4][2] = { {{0, -1}, {-1, 0}, {1, 0}, {0, 1}}, {{-1, 0}, {0, 1}, {0, -1}, {1, 0}} };
const char sig[2][5] = {"LUDR", "URLD"};

int N, M, A[maxn][maxn], V[maxn][maxn];
char str[maxn * maxn];

int build (const int d[4][2], const char* t) {
	int x = 1, y = 1, n = 0; V[1][1] = 1;

	while (true) {
		bool flag = true;
		for (int i = 0; i < 4 && flag; i++) {
			int p = x + d[i][0];
			int q = y + d[i][1];
			if (p <= 0 || p > N || q <= 0 || q > M || V[p][q])
				continue;

			str[n++] = t[i];  V[p][q] = 1;
			x = p, y = q, flag = false;
		}
		if (flag) break;
	}
	str[n] = '\0';
	if (x == N && y == M)
		return n;
	return 0;
}

void build2 (const int d[4][2], const char* t, int& x, int &y, int& n, int l, int r) {
	V[x][y] = 1;

	while (true) {
//		printf("%d %d\n", x, y);
		bool flag = true;
		for (int i = 0; i < 4 && flag; i++) {
			int p = x + d[i][0];
			int q = y + d[i][1];
			if (p <= 0 || p > N || q <= l || q > r || V[p][q])
				continue;

			str[n++] = t[i]; V[p][q] = 1;
			x = p, y = q, flag = false;
		}
		if (flag) break;;
	}
//	printf("end:%d %d\n", x, y);
}

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		memset(V, 0, sizeof(V));

		int k = 1e4 + 5, rx, ry, s = 0;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				scanf("%d", &A[i][j]);
				s += A[i][j];
				if (A[i][j] < k && ((i+j)&1)) {
					k = A[i][j];
					rx = i, ry = j;
				}
			}
		}

		int end = N * M - 1;
		if ((N&1) == 0 && (M&1) == 0) {
			s -= k;
			int x = 1, y = 1, n = 0;
			memset(V, 0, sizeof(V));
			V[rx][ry] = 1;
			for (int i = 1; i <= M; i += 2) {
				if (i == ry || i + 1 == ry)
					build2(dir[1], sig[1], x, y, n, y - 1, y + 1);
				else
					build2(dir[0], sig[0], x, y, n, y - 1, y + 1);
				y++;
				str[n++] = 'R';
			}
			str[n-1] = '\0';
		} else {
			memset(V, 0, sizeof(V));
			int n = build(dir[0], sig[0]);
			if (n != end) {
				memset(V, 0, sizeof(V));
				int n = build(dir[1], sig[1]);
			}
		}

		printf("%d\n%s\n", s, str);
	}
	return 0;
}
