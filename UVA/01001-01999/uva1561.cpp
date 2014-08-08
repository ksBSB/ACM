/**********************
 *
 * 1:有0的情况，如果有方向离权值为0的边的步数为奇数，则为必胜；否则必败；
 * 2:无0的情况，奇数边必胜；
 * 3:有1的情况，同0的判断一样；
 * 4:无1的情况，只剩偶数边的情况，必败；
 *
**********************/


#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 30;

int N, arr[maxn];

bool check (int k) {
	int p = -1;
	while (arr[++p] != k);
	int q = N;
	while (arr[--q] != k);
	q = N - 1 - q;
	return (p&1) || (q&1);
}

bool judge () {
	for (int i = 0; i < N; i++) {
		if (arr[i] == 0)
			return check(0);
	}

	if (N&1)
		return true;

	for (int i = 0; i < N; i++) {
		if (arr[i] == 1)
			return check(1);
	}
	return false;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			scanf("%d", &arr[i]);
		printf("%s\n", judge() ? "YES" : "NO");
	}
	return 0;
}
