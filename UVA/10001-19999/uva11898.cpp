#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxc = 1e4;
const int maxn = 200005;

int N, arr[maxn];
int c[maxc+5];

int solve () {
	int l, r;
	scanf("%d%d", &l, &r);

	if (r - l >= maxc)
		return 0;
	memset(c, 0, sizeof(c));
	
	for (int i = l; i <= r; i++) {
		c[arr[i]]++;
		if (c[arr[i]] == 2)
			return 0;
	}
	int mv = -maxc, ret = maxc;
	for (int i = 1; i <= maxc; i++) {
		if (c[i]) {
			ret = min(ret, i - mv);
			mv = i;
		}
	}
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &N);
		for (int i = 1; i <= N; i++)
			scanf("%d", &arr[i]);

		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			printf("%d\n", solve());
	}
	return 0;
}
