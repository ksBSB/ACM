#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5;

int f[maxn+5];

int getfar(int x) {
	return x == f[x] ? x : f[x] = getfar(f[x]);
}

int main () {
	int x, y;
	while (scanf("%d", &x) == 1) {
		int ret = 0;
		for (int i = 0; i <= maxn; i++)
			f[i] = i;

		while (x != -1) {
			scanf("%d", &y);
			x = getfar(x);
			y = getfar(y);

			if (x == y)
				ret++;
			else
				f[y] = x;
			scanf("%d", &x);
		}
		printf("%d\n", ret);
	}
	return 0;
}
