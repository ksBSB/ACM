#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 105;
const int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int N;
char g[maxn][maxn];

int check (int x, int y) {
	int ret = 0;
	for (int i = 0; i < 4; i++) {
		int p = x + dir[i][0];
		int q = y + dir[i][1];

		if (p < 0 || p >= N || q < 0 || q >= N)
			continue;
		if (g[p][q] == 'x')
			continue;
		ret++;
	}
	return ret;
}

bool judge () {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			if (check(i, j) & 1)
				return false;
	}
	return true;
}

int main () {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%s", g[i]);

	printf("%s\n", judge() ? "YES" : "NO");
	return 0;
}
