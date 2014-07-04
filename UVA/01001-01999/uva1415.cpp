#include <cstdio>
#include <cstring>
#include <cmath>

bool is_prime (int n) {
	int m = sqrt(n+0.5);
	for (int i = 2; i <= m; i++)
		if (n % i == 0)
			return false;
	return true;
}

bool judge (int a, int b) {
	if (a == 0)
		return false;
	return is_prime(a*a+2*b*b);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		int a, b;
		scanf("%d%d", &a, &b);
		printf("%s\n", judge(a, b) ? "Yes" : "No");
	}
	return 0;
}
