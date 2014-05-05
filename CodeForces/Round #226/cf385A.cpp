#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int N = 105;

int n, c, a[N];

int main () {
	int ans = 0;
	scanf("%d%d", &n, &c);
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	for (int i = 1; i < n; i++) ans = max(ans, a[i-1] - a[i]);
	printf("%d\n", max(ans - c, 0));
	return 0;
}
