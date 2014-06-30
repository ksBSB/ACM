#include <stdio.h>
#include <string.h>

const int N = 1005;

int n, x[N], y[N], z[N];

int gcd (int a, int b) {
	return b == 0 ? a : gcd(b, a%b);
}

bool judge (int t, int a, int b) {
	if (a % t == 0 || b % t == 0) return true;
	if (a < 0 && b > 0) return true;
	if (b/t - a/t >= 1) return true;
	return false;
}


bool solve () {
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			int t = gcd(x[i], x[j]);
			if (judge(t, y[j]-z[i], z[j]-y[i])) return false;
		}
	}
	return true;
}

int main () {
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++)
			scanf("%d%d%d", &x[i], &y[i], &z[i]);
		printf("%s\n", solve () ? "Can Take off" : "Cannot Take off");
	}
	return 0;
}
