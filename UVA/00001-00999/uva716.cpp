#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1e6+5;

int n, arr[maxn], t[maxn];
int x, y, z;

ll merge_sort (int l, int r, int* a, int* b) {
	if (l == r)
		return 0;

	ll ret = 0;

	int mid = (r + l) / 2;
	int p = l, q = mid+1, mv = l;

	ret = merge_sort(l, mid, a, b) + merge_sort(mid + 1, r, a, b);

	while (p <= mid || q <= r) {
		if (q > r || (p <= mid && a[p] < a[q]))
			b[mv++] = a[p++];
		else {
			ret += mid - p + 1;
			b[mv++] = a[q++];
		}
	}

	for (int i = l; i <= r; i++)
		a[i] = b[i];
	return ret;
}

bool judge () {
	if (n&1) {
		ll ret = merge_sort(0, n*n*n-1, arr, t) - (z * n * n + x * n + y - 1);
		return (ret&1) == 0;
	}

	while (z != n - 1) {
		int p = z * n * n + x * n + y;
		z++;
		int q = z * n * n + x * n + y;
		swap(arr[p], arr[q]);
	}

	while (x != n - 1) {
		int p = z * n * n + x * n + y;
		x++;
		int q = z * n * n + x * n + y;
		swap(arr[p], arr[q]);
	}

	while (y != n - 1) {
		int p = z * n * n + x * n + y;
		y++;
		int q = z * n * n + x * n + y;
		swap(arr[p], arr[q]);
	}
	ll ret = merge_sort(0, n*n*n-2, arr, t);
	return (ret&1) == 0;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {

		scanf("%d", &n);
		for (int k = 0; k < n; k++) {
			int Z = k * n * n;
			for (int i = 0; i < n; i++) {
				int X = i * n;
				for (int j = 0; j < n; j++) {
					int tmp = Z + X + j;
					scanf("%d", &arr[tmp]);
					if (arr[tmp] == 0) {
						x = i; y = j; z = k;
					}
				}
			}
		}

		printf("%s\n", judge() ? "Puzzle can be solved." : "Puzzle is unsolvable.");
	}
	return 0;
}
