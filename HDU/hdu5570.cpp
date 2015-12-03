#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1005;

int N, M;
double A[maxn][maxn];

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		for (int i = 1; i <= N; i++) {
			double sm = 0;
			for (int j = 1; j <= M; j++) {
				scanf("%lf", &A[i][j]);
				sm += A[i][j];
			}
			for (int j = 1; j <= M; j++) A[i][j] /= sm;
		}

		double ans = 0;
		for (int j = 1; j <= M; j++) {
			double mv = 0;
			for (int i = 1; i <= N; i++) {
				ans += A[i][j] * mv * 2 + A[i][j];
				mv += A[i][j];
			}
		}
		printf("%.2lf\n", ans);
	}
	return 0;
}
