#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define lowbit(x) ((x)&(-x))
const int maxn = 200005;

int N, fenw[maxn], num[maxn];

void add (int x, int v) {
	while (x <= N) {
		fenw[x] += v;
		x += lowbit(x);
	}
}

int sum (int x) {
	int ret = 0;
	while (x) {
		ret += fenw[x];
		x -= lowbit(x);
	}
	return ret;
}

int main () {
	int cas = 0;
	while (scanf("%d", &N) == 1 && N) {
		memset(fenw, 0, sizeof(fenw));
		for (int i = 1; i <= N; i++) {
			scanf("%d", &num[i]);
			add(i, num[i]);
		}

		if (cas)
			printf("\n");
		printf("Case %d:\n", ++cas);

		int x, y;
		char order[15];
		while (scanf("%s", order) == 1 && strcmp(order, "END")) {
			scanf("%d%d", &x, &y);
			if (order[0] == 'M')
				printf("%d\n", sum(y) - sum(x-1));
			else {
				add(x, y - num[x]);
				num[x] = y;
			}
		}
	}
	return 0;
}
