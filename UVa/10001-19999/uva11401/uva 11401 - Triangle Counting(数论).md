#uva 11401 - Triangle Counting(数论)


[题目链接：uva 11401 - Triangle Counting](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=469&page=show_problem&problem=2396)

题目大意：有多少种方法可以从1，2，3...n中选出3个不同的数组成三角形，给出n，求种数。

解题思路：加法原理，设最大边为x的三角形有c(x)个，那么另外两条边长分别为y和z，根据三角形的形式可以的$y+z>x$,所以z的范围即为$x-y<z<x$
                根据这个不等式可以得到每个y值所对应的z值个数，为等差数列，所以
                
$c(x)=\dfrac{\dfrac{(x-1)*(x-2)}{2}-\lfloor\dfrac{x-1}{2}\rfloor}{2}$
然后根据递推：$f(n)=\sum\limits^{n}_{i=1}c(i)$  


####代码

``` c++
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef unsigned long long ll;
const int N = 1e6+5;

ll f[N];
int main () {
	int n;
	f[3] = 0;
	for (ll i = 4; i < N; i++)
		f[i] = f[i-1] + ((i-1)*(i-2)/2 - (i-1)/2)/2;

	while (scanf("%d", &n) == 1 && n >= 3) {
		printf("%llu\n", f[n]);
	}
	return 0;
}


```
            
