#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1030;

#define lowbit(x) ((x)&(-x))
int fenw[maxn+5][maxn+5];

void add (int x, int y, int a) {
	for (int i = x; i <= maxn; i += lowbit(i)) {
		for (int j = y; j <= maxn; j += lowbit(j))
			fenw[i][j] += a;
	}
}

int sum(int x, int y) {
	int ret = 0;
	for (int i = x; i; i -= lowbit(i)) {
		for (int j = y; j; j -= lowbit(j))
			ret += fenw[i][j];
	}
	return ret;
}

int main () {
	int type;
	int s, x, y, a, l, r;
	while (scanf("%d", &type) == 1 && type != 3) {
		if (type == 0) {
			scanf("%d", &s);
			for (int i = 1; i <= s; i++)
				for (int j = 1; j <= s; j++)
					fenw[i][j] = 0;
		} else if (type == 1) {
			scanf("%d%d%d", &x, &y, &a);
			x++; y++;
			add(x, y, a);
		} else {
			scanf("%d%d%d%d", &x, &y, &l, &r);
			x++; y++; l++; r++;
			printf("%d\n", sum(l, r) - sum(x-1, r) - sum(l, y-1) + sum(x-1, y-1));
		}
	}
	return 0;
}
