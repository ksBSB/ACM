#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 105;

int main () {
	int n, k, a[N];
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	sort (a, a + n);

	printf("%d\n", a[n-k]);

	return 0;
}
