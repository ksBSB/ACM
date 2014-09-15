#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 2 * 1e5 + 5;
const int INF = 0x3f3f3f3f;

int N, rec[maxn], arr[maxn];

int bsearch (int v) {
	int l = 0, r = N + 1;
	for (int i = 0; i < 100; i++) {
		int mid = (l + r) / 2;
		if (rec[mid] < v)
			l = mid;
		else
			r = mid;
	}
	return l;
}

int solve () {
	memset(rec, INF, sizeof(rec));
	rec[0] = 0;
	int pre = 0, c = 0, ret = 0;
	for (int i = 1; i <= N; i++) {

		if (arr[i] > pre) {
			c++;
		} else {
			do {
				ret = max(ret, c + bsearch(arr[i-c]));
			} while (--c);

			c = 1;
		}
		rec[c] = min(rec[c], arr[i]);
		pre = arr[i];
	}

	while (c--)
		ret = max(ret, c + bsearch(arr[N-c]) + 1);
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &N);
		for (int i = 1; i <= N; i++)
			scanf("%d", &arr[i]);
		printf("%d\n", solve());
	}
	return 0;
}
