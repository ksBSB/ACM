#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;
const int maxn = 100005;
const int maxm = 15;

int s[maxn][maxm];
int n, k, key, cnt, a[maxm];

void put (int num[]) {
	printf("(%d", num[0]);
	for (int i = 1; i < n; i++)
		printf(",%d", num[i]);
	printf(")\n");
}

bool cmp (int l[], int r[]) {
	for (int i = 0; i < n; i++)
		if (l[i] != r[i])
			return l[i] > r[i];
	return false;
}

void check () {
	int b[maxm*2];
	
	for (int i = 0; i < n; i++)
		b[i] = b[i+n] = a[i];
	for (int i = 0; i < n; i++)
		if (b[i] == a[0] && cmp(b+i, a))
			return;

	for (int i = 0; i < 2 * n; i++)
		b[i] = -b[i];
	for (int i = 0; i < n; i++)
		if (b[i] == a[0] && cmp(b+i, a))
			return;

	for (int i = 0; i < n; i++)
		swap(b[i], b[2*n-i-1]);
	for (int i = 0;  i < n; i++)
		if (b[i] == a[0] && cmp(b+i, a))
			return;

	for (int i = 0; i < 2 * n; i++)
		b[i] = -b[i];
	for (int i = 0; i < n; i++)
		if (b[i] == a[0] && cmp(b+i, a))
			return;

	memcpy(s[cnt++], a, sizeof(a));
}

void dfs (int d, int sum) {
	if (d == n) {
		if (sum == 0)
			check();
		return;
	}

	if (abs(sum) > ((n - d) * a[0]))
		return;

	for (a[d] = -key; a[d] < key; a[d]++) {
		if (a[d-1] == key && a[d] > a[1])
			return;
		dfs(d + 1, sum + a[d]);
	}

	if (a[d] == key && a[d-1] <= a[1])
		dfs(d+1, sum+a[d]);
}

int main () {
	int cas = 0;
	while (scanf("%d%d", &n, &k) == 2 && n) {
		cnt = 1;
		for (a[0] = 1; a[0] <= k; a[0]++) {
			key = a[0];
			dfs(1, key);
		}

		if (cas++)
			printf("\n");
		printf("%d\n", cnt);
		for (int i = 0; i < cnt; i++)
			put(s[i]);
	}
	return 0;
}
