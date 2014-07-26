#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 405;
const int maxm = 10;

int m, n, a[maxn], v[maxn], ans[maxm];

bool check (int x, int* b) {
	memset(a, 0, sizeof(a));
	int tmp = 0;

	for (int i = m-1; i >= 0; i--) {
		tmp = tmp + x * b[i];

		int k = tmp % n;
		a[k]++;
		tmp = tmp / n;

		if (a[k] > v[k])
			return false;
	}

	return tmp == 0;
}

bool judge (int x) {
	int tmp = 0;
	memset(v, 0, sizeof(v));

	for (int i = 0; i < m; i++) {
		tmp = (x + tmp) % n;
		ans[i] = tmp;
		v[ans[i]]++;
	}

	swap(ans[0], ans[m-1]);

	sort(ans, ans + m - 1);
	do {
		bool flag = true;
		if (ans[0] == 0)
			continue;
		for (int i = 2; i <= m; i++) {
			if (check(i, ans)) 
				continue;
			flag = false;
			break;
		}

		if (flag)
			return true;

	} while (next_permutation(ans, ans + m - 1));

	return false;
}

int main () {
	while (scanf("%d%d", &m, &n) == 2 && n + m) {
		bool flag = true;
		for (int i = 1; i < n; i++) {
			if (judge(i)) {
				flag = false;
				break;
			}
		}

		if (flag)
			printf("Not found.\n");
		else {
			printf("%d", ans[0]);
			for (int i = 1; i < m; i++)
				printf(" %d", ans[i]);
			printf("\n");
		}
	}
	return 0;
}
