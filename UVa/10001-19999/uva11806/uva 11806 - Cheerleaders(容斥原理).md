#uva 11806 - Cheerleaders(容斥原理)

[题目链接：uva 11806 - Cheerleaders](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=469&page=show_problem&problem=2906)

题目大意：在一个m行n列的矩阵网里放k个石子，问有多少种画法？每个格子最多放一个石子，所有石子必须用完，并且在第一行、最后一行、第一列和最后一列都得有石子。

解题思路：容斥原理，我们可以先求说在$m*n$的矩阵上放k个石子的种数$C\binom{nm}{k}$,减掉四条边界不放的情况就是答案了。所以枚举16种状态，用二进制数表示说四条边中那些边是不放石子的。

####代码

``` c++
#include <cstdio>
#include <cstring>

const int N = 500;
const int MOD = 1000007;

int n, m, k, C[N+10][N+10];

void init () {

	for (int i = 0; i < N; i++) {
		C[i][0] = C[i][i] = 1;
		for (int j = 1; j < i; j++)
			C[i][j] = (C[i-1][j-1] + C[i-1][j])%MOD;
	}
}

int main () {
	init ();
	
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		scanf("%d%d%d", &n, &m, &k);
		int ans = 0;

		for (int s = 0; s < 16; s++) {
			int cnt = 0, r = n, c = m;

			if (s&1) {
				r--;
				cnt++;
			}

			if (s&2) {
				r--;
				cnt++;
			}

			if (s&4) {
				c--;
				cnt++;
			}

			if (s&8) {
				c--;
				cnt++;
			}

			if (cnt&1)
				ans = (ans + MOD - C[r*c][k])%MOD;
			else
				ans = (ans + C[r*c][k])%MOD;
		}
		printf("Case %d: %d\n", i, ans);
	}

	return 0;
}


```


