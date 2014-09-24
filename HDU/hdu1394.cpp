#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 5005;
#define lowbit(x) ((x)&(-x))

int N, arr[maxn], fenw[maxn];

void add (int x, int v) {
	while (x <= N) {
		fenw[x] += v;
		x += lowbit(x);
	}
}

int sum(int x) {
	int ret = 0;
	while (x) {
		ret += fenw[x];
		x -= lowbit(x);
	}
	return ret;
}

int main () {
	while (scanf("%d", &N) == 1) {
		for (int i = 0; i < N; i++)
			scanf("%d", &arr[i]);
		memset(fenw, 0, sizeof(fenw));

		int s = 0;
		for (int i = N - 1; i >= 0; i--) {
			s += sum(arr[i] + 1);
			add(arr[i] + 1, 1);
		}

		int ans = s;
		for (int i = 0; i < N; i++) {
			s = s + N - arr[i] * 2 - 1;
			ans = min(s, ans);
		}
		printf("%d\n", ans);
	}
	return 0;
}
