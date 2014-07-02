#include <cstdio>
#include <cstring>
#include <cmath>

int countFactor (int x) {
	int ans = 1;
	int m = sqrt(x+0.5);

	for (int i = 2; i <= m; i++) {
		int c = 0;
		while (x % i == 0) {
			x /= i;
			c++;
		}

		ans *= (c + 1);
	}
	if (x > 1)
		ans *= 2;
	return ans;
}

int main () {
	int cas, L, U;
	scanf("%d", &cas);

	while (cas--) {
		scanf("%d%d", &L, &U);
		int ans = 0, id;
		for (int i = L; i <= U; i++) {
			int tmp = countFactor(i);
			if (tmp > ans) {
				ans = tmp;
				id = i;
			}
		}
		printf("Between %d and %d, %d has a maximum of %d divisors.\n", L, U, id, ans);
	}
	return 0;
}
