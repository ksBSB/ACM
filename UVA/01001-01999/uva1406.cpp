#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define lowbit(x) ((x)&(-x))
const int maxn = 1<<16;
const int maxr = 16;

int base[maxr+5], fenx[maxr+5][maxn+5];
int N, add;

int query_treeArr (int* bit, int x) {
	int ret = 0;
	while (x) {
		ret += bit[x];
		x -= lowbit(x);
	}
	return ret;
}

void insert_treeArr (int* bit, int x, int v) {
	while (x <= maxn) {
		bit[x] += v;
		x += lowbit(x);
	}
}

void init () {
	add = 0;
	for (int i = 0; i < maxr; i++) 
		memset(fenx, 0, sizeof(fenx));

	int x;
	for (int i = 0; i < N; i++) {
		scanf("%d", &x);
		for (int j = 1; j <= maxr; j++) {
			insert_treeArr(fenx[j-1], x % base[j] + 1, 1);
		}
	}
}

long long solve () {
	long long ret = 0;
	int x;
	char order[5];

	while (scanf("%s", order) == 1 && strcmp(order, "E")) {
		scanf("%d", &x);
		if (order[0] == 'Q') {
			int have = add % base[x];
			if (add & base[x]) {
				ret += query_treeArr(fenx[x], base[x] - have);
				ret += query_treeArr(fenx[x], base[x+1]) - query_treeArr(fenx[x], base[x+1] - have);
			} else
				ret += query_treeArr(fenx[x], base[x+1] - have) - query_treeArr(fenx[x], base[x] - have);
		} else
			add = (add + x) % base[16];
	}
	return ret;
}

int main () {
	int cas = 1;
	base[0] = 1;
	for (int i = 1; i <= maxr; i++)
		base[i] = base[i-1] * 2;
	while (scanf("%d", &N) == 1 && N != -1) {
		init();
		printf("Case %d: %lld\n", cas++, solve());
	}
	return 0;
}
