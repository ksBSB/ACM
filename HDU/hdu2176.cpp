#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 200005;

int n, sg, arr[maxn];

int main () {
	while (scanf("%d", &n) == 1 && n) {
		sg = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &arr[i]);
			sg ^= arr[i];
		}

		if (sg) {
			printf("Yes\n");
			for (int i = 0; i < n; i++) {
				int tmp = sg ^ arr[i];
				if (arr[i] >= tmp)
					printf("%d %d\n", arr[i], tmp);
			}
		} else
			printf("No\n");
	}
	return 0;
}
