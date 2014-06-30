#include <stdio.h>
const int N = 1005;

int sum(int x) {
	return (1 + x) * x / 2 - 1;
}

int main() {
	int cas, n;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &n);
		int num[N];
		for (int i = 2; i <= n; i++) if (sum(i+1) > n) {
			int s = (n - sum(i)) / (i - 1);
			int t = (n - sum(i)) % (i - 1);

			for (int j = 2; j <= i - t; j++) num[j] = j + s;
			for (int j = i - t + 1; j <= i; j++) num[j] = j + s + 1;
			printf("%d", num[2]);
			for (int j = 3; j <= i; j++) printf(" %d", num[j]);
			printf("\n");
			break;
		}
		if (cas) printf("\n");
	
	}
	return 0;
}
