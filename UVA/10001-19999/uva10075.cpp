#include <cstdio>
#include <cstring>
#include <cmath>
#include <string>
#include <map>
#include <algorithm>
//#include <iostream>

using namespace std;
/* d = r*sqrt(2-2*(cos(lat1)*cos(lat2)*cos(lon1-lon2)+sin(lat1)*sin(lat2)) */

typedef long long ll;
const int maxn = 105;
const double pi = 4 * atan(1);
const double eps = 1e-9;
const double R = 6378;
const int inf = 0x3f3f3f3f;

int N, M, Q, D[maxn][maxn];
char s[maxn], t[maxn];
map<string, int> G;
double lati[maxn], loti[maxn];

double getDistance(double a1, double b1, double a2, double b2) {
	a1 = a1 * pi / 180; a2 = a2 * pi / 180;
	b1 = b1 * pi / 180; b2 = b2 * pi / 180;
	double d = fabs(b1 - b2);
	if (d > pi)
		d = 2 * pi - d;
	return R*acos(cos(a1)*cos(a2)*cos(d)+sin(a1)*sin(a2));
}

void init () {
	G.clear();
	memset(D, inf, sizeof(D));
	for (int i = 1; i <= N; i++) {
		scanf("%s%lf%lf", s, &lati[i], &loti[i]);
		G[s] = i;
		D[i][i] = 0;
	}

	for (int i = 1; i <= M; i++) {
		scanf("%s%s", s, t);
		int u = G[s], v = G[t];
		D[u][v] = (int)(getDistance(lati[u], loti[u], lati[v], loti[v]) + 0.5);
	}
}

void Floyd () {
	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++)
				D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
		}
	}
}

int main () {
	int cas = 0;
	while (scanf("%d%d%d", &N, &M, &Q) == 3 && N+M+Q) {
		init();

		Floyd();
		if (cas) printf("\n");
		printf("Case #%d\n", ++cas);
		for (int i = 1; i <= Q; i++) {
			scanf("%s%s", s, t);
			int u = G[s], v = G[t];
			if (D[u][v] == inf) {
				printf("no route exists\n");
			} else
				printf("%d km\n", D[u][v]);
		}
	}
	return 0;
}
