#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 5;

int N, M, K, Q, X[maxn], Y[maxn];

void init () {
	scanf("%d%d%d%d", &N, &M, &K, &Q);
	memset(X, 0, sizeof(X));
	memset(Y, 0, sizeof(Y));

	int x, y;
	while (K--) {
		scanf("%d%d", &x, &y);
		X[x] = Y[y] = 1;
	}
	for (int i = 1; i <= N; i++) X[i] += X[i-1];
	for (int i = 1; i <= M; i++) Y[i] += Y[i-1];
}

bool judge (int x1, int y1, int x2, int y2) {
	return x2-x1+1 == X[x2]-X[x1-1] || y2-y1+1 == Y[y2]-Y[y1-1];
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		int x1, y1, x2, y2;
		while (Q--) {
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			printf("%s\n", judge(x1, y1, x2, y2) ? "Yes" : "No");
		}
	}

	return 0;
}
