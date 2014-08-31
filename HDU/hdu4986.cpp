#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 1e6;

double p[maxn+5];

void init () {
	p[1] = 1;
	for (int i = 2; i <= maxn; i++)
		p[i] = p[i-1] + 1.0 / i;
}

int main () {
	init();
	int n;
	while (scanf("%d", &n) == 1) {
		printf("%.4lf\n", n >= maxn ? 0.577215664901 + log((double)n) : p[n]);
	}
	return 0;
}
