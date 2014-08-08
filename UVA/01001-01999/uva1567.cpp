/*******************
 * K倍动态减法游戏
 * 参考：http://www.cnblogs.com/jianglangcaijin/archive/2012/12/19/2825539.html
*******************/


#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e6+5;

int N, K, a[maxn], b[maxn];

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		scanf("%d%d", &N, &K);
		int p = 0, q = 0;
		a[0] = b[0] = 0;
		while (a[p] < N) {
			a[p+1] = b[p] + 1;
			p++;

			while (a[q + 1] * K < a[p])
				q++;
			b[p] = b[q] + a[p];
		}

		printf("Case %d: ", i);
		if (N == a[p])
			printf("lose\n");
		else {
			int ans;
			while (N) {
				if (N >= a[p]) {
					N -= a[p];
					ans = a[p];
				}
				p--;
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}
