#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5+5;

int N, a[maxn];

int solve () {
	int cnt = 1;
	for (int i = 1; i <= N; i++) {
		if (a[i] == 1 && a[i-1] == 2)
			cnt++;
		else if (a[i] == 2 && a[i-1] == 1)
			cnt++;
		else if (a[i] - a[i-1] > 3 || a[i-1] - a[i] > 3)
			return 0;
		else if (a[i] == a[i-1] && a[i] != 1)
			return 0;
	}
	if (a[N] == 0)
		return cnt;
	else
		return cnt * 2;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%d", &N);
		for (int i = 1; i <= N; i++)
			scanf("%d", &a[i]);
		printf("Case #%d: %d\n", kcas, solve());
	}
	return 0;
}
