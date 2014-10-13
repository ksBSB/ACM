#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

int N;

double f(double x, int k) {
	if (x == 0)
		return 0;

	if (k == 1)
		return x * log2(x);
	else if (k == 2)
		return x * log(x);
	else
		return x * log10(x);
}

int main () {
	int cas, k;
	scanf("%d", &cas);
	while (cas--) {
		char op[10];
		scanf("%d%s", &N, op);
		if (op[0] == 'b')
			k = 1;
		else if (op[0] == 'n')
			k = 2;
		else if (op[0] == 'd')
			k = 3;

		int x;
		double ans = 0;
		for (int i = 1; i <= N; i++) {
			scanf("%d", &x);
			ans += f(x / 100.0, k);
		}
		printf("%.8lf\n", -ans);
	}
	return 0;
}
