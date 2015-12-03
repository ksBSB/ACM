#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 10;

int X[maxn], Y[maxn];

bool solve(int* x, int* y) {
	if (x[0] == x[1] && x[1] == x[2]) return true;
	//if (y[0] == y[1] && y[1] == y[2]) return true;
	if (x[0] + x[1] == x[2] && y[0] == y[1]) return true;
	return false;
}

bool judge () {
	int tmpx[maxn], tmpy[maxn];
	for (int i = 0; i < 4; i++) {
		tmpx[0] = X[i];
		tmpy[0] = Y[i];

		for (int j = 0; j < 4; j++) {
			if (i == j) continue;

			tmpx[1] = X[j];
			tmpy[1] = Y[j];

			for (int k = 0; k < 4; k++) {
				if (k == i || k == j) continue;

				tmpx[2] = X[k];
				tmpy[2] = Y[k];

				for (int s = 0; s < 8; s++) {
					for (int t = 0; t < 3; t++) if (s&(1<<t)) swap(tmpx[t], tmpy[t]);
					if (solve(tmpx, tmpy)) return true;
					for (int t = 0; t < 3; t++) if (s&(1<<t)) swap(tmpx[t], tmpy[t]);
				}
			}
		}
	}
	return false;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		for (int i = 0; i < 4; i++) scanf("%d%d", &X[i], &Y[i]);
		printf("%s\n", judge() ? "Yes" : "No");
	}
	return 0;
}
