#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main () {
	int n, m, a, b;
	scanf("%d%d%d%d", &n, &m, &a, &b);
	int k = n / m, ans = 0;
	ans = min(k * m * a, k * b);
	k = n % m;
	ans += min(k * a, b);
	printf("%d\n", ans);
	return 0;
}
