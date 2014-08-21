#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e6;

int k[maxn+5];
double arr[maxn+5];

void init (int n) {
	arr[1] = 5;
	k[1] = 1;
	for (int i = 2; i <= n; i++) {
		arr[i] = 0.5 * arr[i-1];
		k[i] = k[i-1];

		while (arr[i] < 1.0) {
			arr[i] *= 10;
			k[i]++;
		}
	}
}

int main () {
	int n;
	init(maxn);
	while (scanf("%d", &n) == 1) {
		printf("2^-%d = %.3lfe-%d\n", n, arr[n], k[n]);
	}
	return 0;
}
