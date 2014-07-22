#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 20;

char s[N][N];
bool flag;
int g[N][N], ans[8][4];
int c[N], can[N][N], v[N];

bool init () {
	flag = false;
	char str[N];
	memset(g, 0, sizeof(g));
	memset(c, 0, sizeof(c));

	for (int i = 0; i < 3; i++) {
		memset(v, 0, sizeof(v));
		for (int j = 0; j < 4; j++) {

			if (scanf("%s", str) == 1) {

				for (int t = 0; t < 4; t++) {
					if (v[str[t]-'A']) flag = true;
					v[str[t]-'A'] = 1;

					for (int k = 0; k < 4; k++) {
						if (t == k) continue;
						g[str[t]-'A'][str[k]-'A']++;
					}
					g[str[t]-'A'][str[t]-'A'] = 1;
				}
			} else 
				return false;
			memcpy(s[i*4+j], str, sizeof(str));
		}
	}


	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			if (g[i][j] == 0) {
				can[i][c[i]++] = j;
			}
		}
	}
	memset(v, 0, sizeof(v));
	return true;
}

int getX (int* x) {
	for (int i = 0; i < 4; i++)
		if (v[x[i]] == 1) return x[i];
	return -1;
}

void putAns() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			if (j) printf("	");
			printf("%s", s[i*4+j]);
		}
		printf("\n");
	}
	for (int k = 0; k < 2; k++) {
		for (int i = k; i < 8; i += 2) {
			if (i/2) printf("	");
			for (int j = 0; j < 4; j++)
				printf("%c", 'A' + ans[i][j]);
		}
		printf("\n");
	}
}

bool judge (int x, int* y) {
	for (int i = 0; i < 4; i++)
		if (y[i] == x) return false;
	return true;
}

bool DFS (int d) {

	if (d == 8) {
		putAns();
		return true;
	}

	if (d == 0) {
		do {
			ans[d][0] = 0;
			memcpy (ans[d]+1, can[0], sizeof(int)*3);

			for (int i = 0; i < 4; i++) v[ans[d][i]]++;

			if (DFS(d+1)) return true;

			for (int i = 0; i < 4; i++) v[ans[d][i]]--;

		} while (next_permutation (can[0], can[0] + c[0]));
	} else {
		int x = getX(ans[d-1]);
		if (x == -1) return false;

		int cnt = 1;
		ans[d][0] = x;
		for (int i = 0; i < c[x]; i++) {
			int& u = can[x][i];
			if (v[u] < 2 && judge (u, ans[d-1])) {
				ans[d][cnt++] = can[x][i];
			}
		}

		if (cnt != 4) return false;

		for (int i = 0; i < 4; i++) v[ans[d][i]]++;

		if (DFS(d+1)) return true;

		for (int i = 0; i < 4; i++) v[ans[d][i]]--;
	}

	return false;
}

int main () {
	while (init ()) {

		if (flag || !DFS (0))
			printf("It is not possible to complete this schedule.\n");
		printf("\n");
	}
	return 0;
}
