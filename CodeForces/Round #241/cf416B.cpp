#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 50005; 
int m, n, ans[N];

int main () {
	int v[10];
	memset(v, 0, sizeof(v));

	scanf("%d%d", &m, &n);
	for (int i = 1; i <= m; i++) {
		int t = 0, a;
		for (int j = 0; j < n; j++) {
			scanf("%d", &a);
			int s = max(v[j], t);
			t = s + a;
			v[j] = t;
		}
		ans[i] = t;
	}
	for (int i = 1; i < m; i++)
		printf("%d ", ans[i]);
	printf("%d\n", ans[m]);
	return 0;
}
