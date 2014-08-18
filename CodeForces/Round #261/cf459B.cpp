#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 2 * 1e5 + 5;
typedef long long ll;

int n, b[maxn];

int main () {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &b[i]);
	sort(b, b + n);
	int dis = b[n-1] - b[0];

	ll p = 0, q = n-1, ans;

	if (dis == 0) {
		ans = (ll)n * (n - 1) / 2;
	} else {
		while (b[p] == b[0] && p < n) p++;
		while (b[q] == b[n-1] && q >= 0) q--;
		ans = p * (n-1-q);
	}
	printf("%d %lld\n", dis, ans);
	return 0;
}
