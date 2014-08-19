#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 10;
const int maxm = 400;
const double INF = 0x3f3f3f3f;

double l[maxn+5][maxm+5], r[maxn+5][maxm+5];

inline double cal (int k) {
	if (k < 10)
		return 2.0;
	else if (k < 15)
		return 2.5;
	else if (k < 20)
		return 3.0;
	else if (k < 25)
		return 3.5;
	else
		return 4.0;
}

void init () {
	for (int i = 0; i <= maxn; i++) {
		for (int j = 0; j <= maxm; j++) {
			l[i][j] = 50;
			r[i][j] = 0;
		}
	}
	l[0][0] = r[0][0] = 0;

	for (int i = 0; i < maxn; i++) {
		for (int j = 0; j <= maxm; j++) {
			for (int k = 0; k <= 40; k++) {

				if (j + k > maxm)
					break;

				l[i+1][j+k] = min(l[i+1][j+k], l[i][j] + cal(k));
				r[i+1][j+k] = max(r[i+1][j+k], r[i][j] + cal(k));
			}
		}
	}
}

int main () {
	init();
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		int score, n;
		scanf("%d%d", &score, &n);
		score = (score - 60) * n;
		printf("%.4lf %.4lf\n", l[n][score] / n, r[n][score] / n);
	}
	return 0;
}
