#include <stdio.h>
#include <string.h>

const int N = 105;
int n, num[N];

int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}

int main () {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", &num[i]);
	int t = num[0];
	for (int i = 1; i < n; i++) t = gcd(t, num[i]);
	printf("%d\n", t * n);
	return 0;
}
