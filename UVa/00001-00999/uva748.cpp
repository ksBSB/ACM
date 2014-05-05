#include <stdio.h>
#include <string.h>

const int N = 1005;
int n, a[N], b[N], na, nb;

int find(char *str) {
	int len = strlen(str);
	for (int i = len - 1; i >= 0; i--) if (str[i] == '.') return len - i - 1;
	return 0;
}

void init(char *num) {
	na = nb = 0;
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));

	int len = strlen(num);
	for (int i = len - 1; i >= 0; i--) if (num[i] != '.') 
		a[na++] = num[i] - '0';

	b[0] = nb = 1;
}

void put(int *num, int k, int cnt) {
	char str[N];
	int r = 0, l = 0;
	for (int i = cnt - 1; i >= 0; i--) {
		if (i == k - 1) str[r++] = '.';
		str[r++] = '0' + num[i];
	}

	while (str[l] == '0') l++;
	while (str[r - 1] == '0') r--;

	if (str[r - 1] == '.') r--;
	for (int i = l; i < r; i++) printf("%c", str[i]);
	printf("\n");
}

void mul(int* x, int* y, int& nx, int& ny) {

	int sum, ans[N], tmp = 0;
	memset(ans, 0, sizeof(ans));
	for (int i = 0; i < nx; i++) {
		sum = 0;
		for (int j = 0; j < ny; j++) {
			sum = x[i] * y[j] + ans[i + j] + sum;
			ans[i + j] = sum % 10;
			sum /= 10;
		}

		int t = i + ny;
		while (sum) {
			ans[t++] = sum % 10;
			sum /= 10;
		}
		if (t > tmp) tmp = t;
	}

	nx = tmp;
	memcpy(x, ans, sizeof(ans));
}

void solve(int k) {
	for (int i = 0; i < n; i++) mul(b, a, nb, na);
	put(b, k, nb);
}

int main () {
	char num[N];
	while (scanf("%s%d", num, &n) == 2) {
		int k = find(num); k *= n;
		init(num);
		solve(k);
	}
	return 0;
}
