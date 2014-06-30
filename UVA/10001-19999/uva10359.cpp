#include <stdio.h>
#include <string.h>
#define ll long long
#define max(a, b) (a)>(b)?(a):(b)
const int N = 255;

int cnt[N][N];

void add(int ans[], int a[], int b[]) {
	int sum = 0;
	ans[0] = max(a[0], b[0]);
	for (int i = 1; i <= ans[0]; i++) {
		if (i <= a[0]) sum += a[i];
		if (i <= b[0]) sum += b[i] * 2;
		ans[i] = sum % 10;
		sum /= 10;
	}

	while (sum) {
		ans[++ans[0]] = sum % 10;
		sum /= 10;
	}
}


void init() {
	memset(cnt, 0, sizeof(cnt));
	cnt[0][0] = cnt[1][0] = cnt[0][1] = cnt[1][1] = 1;
	for (int i = 2; i < N; i++)
		add(cnt[i], cnt[i - 1], cnt[i - 2]);
}

int main () {
	int n;
	init();
	while (scanf("%d", &n) == 1) {
		for (int i = cnt[n][0]; i; i--)
			printf("%d", cnt[n][i]);
		printf("\n");
	}
	return 0;
}
