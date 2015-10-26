#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 105;
const int inf = 0x3f3f3f3f;

int M, N;
double X[maxn], Y[maxn], D[maxn][maxn];

double dis(double x, double y) {
	return sqrt(x*x + y*y);
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%d%d", &M, &N);
		for (int i = 1; i <= M; i++) {
			scanf("%lf%lf", &X[i], &Y[i]);
			for (int j = 1; j <= i; j++)
				D[i][j] = D[j][i] = dis(X[i]-X[j], Y[i]-Y[j]);
		}

		int ans = inf;
		for (int i = 1; i <= M; i++) {
			sort(D[i] + 1, D[i] + 1 + M);
			int r = ceil(D[i][N]);
			for (int k = 0; k < 2; k++) {
				int c = 0, flag = 1;
				for (int j = 1; j <= M && flag; j++) {
					if (fabs(D[i][j] - r) < 1e-6) flag = 0;
					if (D[i][j] < r) c++;
				}

				if (flag && c == N) {
					ans = min(ans, r);
				}
				r++;
			}
		}
		if (ans == inf) ans = -1;
		printf("%d\n", ans);
	}
	return 0;
}
