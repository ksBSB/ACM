#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>

using namespace std;

const int N = 10005;
int n, k, num[N];

bool cmp(const int& a, const int& b) {
	int p = abs(a), q = abs(b);
	if (p != q) return p > q;
	else return a > b;
}

void init() {
	for (int i = 0; i < n; i++) scanf("%d", &num[i]);
	sort(num, num + n, cmp);
}

int handle(int t) {
	sort(num, num + n);
	int sum = 0;
	for (int i = 1; i <= t; i++) {
		sum += num[n-i];
	}
	return sum;
}

int solve() {
	int sum = 0, cnt = 0, p = 0, q = 0;
	bool flag = false;
	for (int i = 0; i < k; i++) {
		if (num[i] == 0) {
			flag = true; break;
		} else if (num[i] < 0) {
			cnt++; q = num[i];
		} else p = num[i];
		sum += num[i];
	}
	
	if (flag) return handle(k);
	else if (cnt % 2 && k < n) {
		int x = 0, y = 0, bo = 0;
		for (int i = k; i < n; i++) if (num[i] > 0) {
			x = num[i]; break;	
		}
		for (int i = k; i < n; i++) if (num[i] < 0) {
			y = num[i]; break;
		}
		for (int i = k; i < n; i++) if (num[i] == 0) {
			bo = 1; break;
		}

		if (p == 0) {
			if (x) sum = sum - q + x;
			else sum = handle(k);
		} else {
			if (x == 0 && y == 0) sum = handle(k - 1);
			else if (x == 0) sum = sum - p + y;
			else if (y == 0) sum = sum - q + x;
			else if (x * p >= y * q) sum = sum - q + x;
			else sum = sum - p + y;
		}
	}
	return sum;
}

int main() {
	while (scanf("%d%d", &n, &k) == 2 && n + k) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}
