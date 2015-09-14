#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 5;
const int inf = 1e9;

int N, nth[maxn];

bool judge (int m) {
	for (int i = 1; i < N; i++)
		if (nth[i] == m)
			return true;
	return false;
	//int k = lower_bound(nth, nth + N, m) - nth;
	//return nth[k] == m;
}

int solve (int m) {
	if (judge(m))
		return 1;

	for (int i = 1, j = N-1; i < N && nth[i] < m; i++) {
		while (nth[i] + nth[j] > m)
			j--;
		if (nth[i] + nth[j] == m)
			return 2;
	}

	for (int i = 3; i <= 8; i++) {
		if ((m-i) % 6 == 0)
			return i;
	}
	return -1;
}

int main () {
	N = 1;
	while (nth[N-1] <= inf) {
		nth[N] = 3 * N * (N-1) + 1;
		N++;
	}
	N--;

	int cas, m;
	scanf("%d", &cas);
	for (int i = 0; i < cas; i++) {
		scanf("%d", &m);
		printf("%d\n", solve(m));
	}
	return 0;
}
