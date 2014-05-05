#include <stdio.h>
#include <string.h>

const int N = 20;
int n, t[N];

void solve (int bit) {
	int b = (bit+1)/2, ans[N];

	for (int i = 1; i <= b; i++) {
		ans[i] = n / t[b-i] + (i == 1 ? 1 : 0);
		n = n % t[b-i];
		if (n == 0 && i != b) {
			ans[i]--;
			n = t[b-i];
		}
	}

	ans[b]--;

	for (int i = 1; i <= b; i++)
		printf("%d", ans[i]);
	if (bit%2 == 0) printf("%d", ans[b]);
	for (int i = b - 1; i > 0; i--)
		printf("%d", ans[i]);
	printf("\n");
}

int main () {
	t[0] = 1;
	for (int i = 1; i <= 9; i++)
		t[i] = t[i-1] * 10;

	while (scanf("%d", &n) == 1 && n) {

		for (int i = 1; i; i++) {
			int k = t[(i-1)/2] * 9;
			if (k >= n) {
				solve (i);
				break;
			}
			n -= k;
		}
	}
	return 0;
}
