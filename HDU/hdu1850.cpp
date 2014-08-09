/*****************
 *
 * sg 为0时，有arr[i] ^ sg == arr[i]，所以arr[i] > arr[i] ^ sg；
*****************/

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 105;

int n, sg, c, arr[maxn];

int main () {

	while (scanf("%d", &n) == 1 && n) {
		sg = c = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &arr[i]);
			sg ^= arr[i];
		}

		for (int i = 0; i < n; i++) {
			int tmp = sg ^ arr[i];
			if (arr[i] > tmp)
				c++;
		}
		printf("%d\n", c);
	}

	return 0;
}
