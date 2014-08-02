#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

int main () {
	int n, m;
	scanf("%d%d", &m, &n);

	double ans = 0;
	for (int i = 1; i < m; i++)
		ans += pow((double)i / m, n);
	printf("%.12lf\n", (double) m - ans);
	return 0;
}
