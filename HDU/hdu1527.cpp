/*****************
 * 威佐夫博弈
*****************/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

int main () {
	int a, b;
	while (scanf("%d%d", &a, &b) == 2) {
		if (a > b)
			swap(a, b);
		int k = b - a;
		printf("%d\n", a == (int)(k * (1 + sqrt(5.0)) / 2) ? 0 : 1);
	}
	return 0;
}
