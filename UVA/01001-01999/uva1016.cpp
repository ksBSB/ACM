#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1005;

int n, arr[maxn], rec[maxn], pos[maxn];
int rep, v[maxn];

void init () {
	memset(v, 0, sizeof(v));
	memset(rec, -1, sizeof(rec));

	rep = maxn;
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
		pos[i] = arr[i];
		rep = min(arr[i], rep);
	}

	sort(pos, pos + n);
	for (int i = 0; i < n; i++)
		rec[pos[i]] = i;

	for (int i = 0; i < n; i++)
		pos[i] = rec[arr[i]];

	/*
	for (int i = 0; i < n; i++)
		printf("%d ", pos[i]);
	printf("\n");
	*/
}

int solve () {
	int ret = 0;

	for (int i = 0; i < n; i++) {
		if (v[i])
			continue;

		int j = i, c= 0;
		int ans = 0, tmp = maxn;

		while (v[j] == 0) {
			tmp = min(tmp, arr[j]);
			ans += arr[j];

			v[j] = 1;
			c++;

			j = pos[j];
		}

		ans -= tmp;

		ret += ans + min(tmp * (c-1), tmp * 2 + rep * (c+1));
	}
	return ret;
}

int main () {
	int cas = 1;
	while (scanf("%d", &n) == 1 && n) {
		init();
		printf("Case %d: %d\n\n", cas++, solve());
	}
	return 0;
}
