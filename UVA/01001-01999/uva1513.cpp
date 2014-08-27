#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define lowbit(x) ((x)&(-x))
const int maxn = 1e5+5;

int N, M, fenw[maxn*2], pos[maxn];

void add (int x, int v) {
	while (x < 2*maxn) {
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
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d", &N, &M);
		memset(fenw, 0, sizeof(fenw));
		int n = N, x;
		for (int i = 1; i <= N; i++) {
			pos[i] = N - i + 1;
			add(pos[i], 1);
		}

		for (int i = 1; i <= M; i++) {
			scanf("%d", &x);
			printf("%d%c", n - sum(pos[x]), i == M ? '\n' : ' ');
			add(pos[x], -1);
			pos[x] = ++N;
			add(pos[x], 1);
		}
	}
	return 0;
}
