#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

bool judge (int n, int k) {
	int pos = 0;
	for (int i = 2 * n; i > n; i--) {
		pos = (pos - 1 + k) % i;
		if (pos < n)
			return false;
	}
	return true;
}

int solve (int n) {
	for (int i = n+1; true; i++)
		if (judge(n, i))
			return i;
}

int main () {
	int n, ans[15];
	for (int i = 1; i <= 14; i++)
		ans[i] = solve(i);
	while (scanf("%d", &n) == 1 && n) {
		printf("%d\n", ans[n]);
	}
	return 0;
}
