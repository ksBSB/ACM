#include <stdio.h>
typedef long long ll;

int main() {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		ll n, s = 1;
		scanf("%lld", &n);
		n++;
		if (n == 1) printf("Case %d: 0\n", i);
		else {
			int j;
			for (j = 0; s < n; j++) s *= 2;
			printf("Case %d: %d\n", i, j);
		}
	}
	return 0;
}
