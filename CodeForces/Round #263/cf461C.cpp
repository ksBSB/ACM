#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e6+5;

int N, Q, W[maxn];

int main () {
	scanf("%d%d", &N, &Q);
	for (int i = 1; i <= N; i++)
		W[i] = i;

	bool flag = false;
	int k, l, r;
	int n = N, bw = 0;

	while (Q--) {
		scanf("%d%d", &k, &l);

		if (k == 1) {
			if (l > n - l) {
				flag = !flag;
				l = n - l;
			}

			if (flag) {

				for (int i = 0; i < l; i++)
					W[bw + n - l - i] += N - W[bw + n - l + i];

			} else {
				bw += l;
				for (int i = 0; i < l; i++)
					W[bw + i] -= W[bw - i];
			}
			n -= l;

		} else {
			scanf("%d", &r);
			if (flag) {
				int tmp = n - r;
				r = n - l;
				l = tmp;
			}
			printf("%d\n", W[bw + r] - W[bw + l]);
		}
	}
	return 0;
}
