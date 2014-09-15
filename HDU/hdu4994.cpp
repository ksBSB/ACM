#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1005;

int n, arr[maxn];

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &n);

		for (int i = 1; i <= n; i++)
			scanf("%d", &arr[i]);
		int ret = 0;
		for (int i = 1; i < n; i++) {
			if (arr[i] != 1)
				break;
			else
				ret++;
		}
		printf("%s\n", ret&1 ? "No" : "Yes");
	}
	return 0;
}
