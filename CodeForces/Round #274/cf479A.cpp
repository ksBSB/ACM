#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
int a[3];

int solve (int s) {
	int ret = 0;

	for (int i = 0; i < 2; i++) {
		int tmp = 0, d = 1 - i;
		if (s&(1<<i))
			tmp = a[i] * a[i+1];
		else
			tmp = a[i] + a[i+1];

		if (s&(1<<d))
			tmp = tmp * a[(i+2)%3];
		else
			tmp = tmp + a[(i+2)%3];
		ret = max(ret, tmp);
	}
	return ret;
}

int main () {

	for (int i = 0; i < 3; i++)
		scanf("%d", &a[i]);

	int ans = 0;
	for (int i = 0; i < 4; i++)
		ans = max(ans, solve(i));
	printf("%d\n", ans);
	return 0;
}
