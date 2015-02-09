#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 5005;
int C[5], A[5][maxn];

int main () {
	int n, x;
	memset(C, 0, sizeof(C));
	
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &x);
		A[x][++C[x]] = i;
	}

	for (int i = 1; i <= 3; i++)
		n = min(n, C[i]);

	printf("%d\n", n);
	for (int i = 1; i <= n; i++)
		printf("%d %d %d\n", A[1][i], A[2][i], A[3][i]);
	return 0;
}
