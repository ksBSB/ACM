#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 105;

int n, arr[maxn];

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d", &arr[i]);

		int ans = 0;
		for (int i = 1; i < n - 1; i++)
			if (arr[i] > arr[i-1] && arr[i] > arr[i+1])
				ans++;
		printf("%d\n", ans);
	}
	return 0;
}
