#uva 11538 - Chess Queen(数论)


[题目链接：uva 11538 - Chess Queen](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=469&page=show_problem&problem=2533)

题目大意：在一个$n*m$的棋盘上，放两个皇后，要求两个皇后可以互相攻击，求有多少种放法。

解题思路：因为皇后的攻击范围为竖线、横线和斜线，所以枚举每条上两个皇后放的位置，比如一条斜线有8个，那么放两个皇后的种数就有$C\binom{8}{2}$种。
                行数n，每行m个位置$C\binom{m}{2}*n$
                列数m，每列n个位置$C\binom{n}{2}*m$
                斜线，$2*(2 * \sum\limits^{n-1}_{i=1} i*(i-1) + (m-n+1) * n * (n-1))$,因为正斜线和翻斜线，所以要乘以2
                最后公式化简为$\dfrac{2*n*(n-1)*(3*m-n-1)}{3}$
                

####代码：             
``` c++
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;
typedef unsigned long long ll;

ll n, m;
int main () {
	while (cin >> n >> m) {
		if (!(n + m))
			break;

		if (m < n)
			swap(n, m);

		cout << n * m * (n+m-2) + 2 * n * (n-1)*(3*m-n-1)/3 << endl;
	}
	return 0;
}
```