#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int solve(int a, int b, int c) {
	return max(a, min(b, (c+1)/2));
}

int main () {
	int n, m, x, y;
	while (scanf("%d%d%d%d", &n, &m, &x, &y) == 4) {
		int p = min(x, n - x + 1);
		int q = min(y, m - y + 1);
		int ans;
		if (x == n - x + 1 && y == m - y + 1) 
			ans = min(x, y) - (n == m ? 1 : 0);
		else
			ans = min(solve(p, n-p, m), solve(q, m-q, n));

		printf("%d\n", ans);
	}
	return 0;
}
