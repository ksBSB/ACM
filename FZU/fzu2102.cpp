#include <stdio.h>
#include <string.h>

const int N = 100;

int bas, n, m;

int changeBase(char num[], int b) {
	int len = strlen(num);
	int ans = 0, k;
	for (int i = 0; i < len; i++) {
		if (num[i] >= '0' && num[i] <= '9') k = num[i] - '0';
		else k = num[i] - 'a' + 10;
		ans = ans * b + k;
	}
	return ans;
}

int main () {
	int cas;
	char a[N], b[N];
	scanf("%d", &cas);
	while (cas--) {
		scanf("%s%s%d", a, b, &bas);
		n = changeBase(a, bas);
		m = changeBase(b, bas);
		int ans = n / m;
		printf("(%d,%d)\n", ans, n - ans * m);
	}
	return 0;
}
