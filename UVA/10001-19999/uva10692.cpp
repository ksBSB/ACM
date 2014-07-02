#include <cstdio>
#include <cstring>
#include <cmath>

const int maxn = 15;

int A[maxn], k;

int pow_mod (int a, int n, int M) {
	int ans = 1;

	while (n) {
		if (n&1)
			ans = ans * a % M;
		a = a * a % M;
		n /= 2;
	}
	return ans;
}

int euler_phi(int n) {
	int m = (int)sqrt(n+0.5);
	int ans = n;
	for (int i = 2; i <= m; i++) {
		if (n % i == 0) {
			ans = ans / i * (i-1);
			while (n%i==0)
				n /= i;
		}
	}

	if (n > 1)
		ans = ans / n * (n - 1);
	return ans;
}

int solve (int d, int M) {
	if (d == k - 1)
		return A[d]%M;

	int phi = euler_phi(M);
		int c = solve (d+1, phi) + phi;
	return pow_mod(A[d], c, M);
}

int main () {
	int cas = 1;
	char str[maxn];

	while (scanf("%s", str) == 1 && strcmp(str, "#")) {
		int M;
		sscanf(str, "%d", &M);
		scanf("%d", &k);
		for (int i = 0; i < k; i++)
			scanf("%d", &A[i]);

		printf("Case #%d: %d\n", cas++, solve(0, M));
	}
	return 0;
}
