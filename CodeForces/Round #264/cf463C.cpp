#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define add(a,b) ((a)+(b))
#define del(a,b) ((a)-(b)+2000)

const int maxn = 2005;
typedef long long ll;

int n;
ll g[maxn][maxn], l[maxn*2], r[maxn*2];

int main () {
	scanf("%d", &n);
	memset(l, 0, sizeof(l));
	memset(r, 0, sizeof(r));

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			scanf("%lld\n", &g[i][j]);
			l[add(i, j)] += g[i][j];
			r[del(i, j)] += g[i][j];
		}

	int odd_x, odd_y, even_x, even_y;
	ll max_odd = -1, max_even = -1;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if ((i+j)&1) {
				if (max_odd < l[add(i, j)] + r[del(i, j)] - g[i][j]) {
					max_odd = l[add(i, j)] + r[del(i, j)] - g[i][j];
					odd_x = i;
					odd_y = j;
				}
			} else {
				if (max_even < l[add(i, j)] + r[del(i, j)] - g[i][j]) {
					max_even = l[add(i, j)] + r[del(i, j)] - g[i][j];
					even_x = i;
					even_y = j;
				}
			}
		}
	}
	printf("%lld\n%d %d %d %d\n", max_even + max_odd, odd_x, odd_y, even_x, even_y);
	return 0;
}
