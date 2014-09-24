#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 200005;
#define lowbit(x) ((x)&(-x))

int N, fenw[maxn], pos[maxn], val[maxn], rec[maxn];

void add (int x, int v) {
	while (x <= N) {
		fenw[x] += v;
		x += lowbit(x);
	}
}

int find (int x) {
	int p = 0, s = 0;
	for (int i = 20; i >= 0; i--) {
		p += (1<<i);
		if (p > N || s + fenw[p] >= x)
			p -= (1<<i);
		else
			s += fenw[p];
	}
	return p + 1;
}

int main () {
	while (scanf("%d", &N) == 1) {
		memset(fenw, 0, sizeof(fenw));
		for (int i = 1; i <= N; i++) {
			add(i, 1);
			scanf("%d%d", &pos[i], &val[i]);
		}

		for (int i = N; i; i--) {
			int tmp = find(pos[i] + 1);
			rec[tmp] = i;
			add(tmp, -1);
		}
		
		for (int i = 1; i <= N; i++)
			printf("%d%c", val[rec[i]], i == N ? '\n' : ' ');
	}
	return 0;
}
