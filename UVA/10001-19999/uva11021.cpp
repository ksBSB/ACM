/*********************
 *
 * pi 为出生i麻球的概率
 * fi 为1只麻球在i天内死亡的概率
*********************/

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 1005;

int n, k, m;
double p[maxn], f[maxn];

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%d%d%d", &n, &k, &m);
		for (int i = 0; i < n; i++)
			scanf("%lf", &p[i]);
		f[0] = 0;
		f[1] = p[0];
		for (int i = 1; i <= m; i++) {
			f[i] = 0;
			for (int j = 0; j < n; j++)
				f[i] += p[j] * pow(f[i-1], j);
		}
		printf("Case #%d: %.7lf\n", kcas, pow(f[m], k));
	}
	return 0;
}
