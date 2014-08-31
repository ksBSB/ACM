#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 3 * 1e5 + 5;

int N, arr[maxn];

int main () {
	scanf("%d", &N);

	ll sum = 0;
	for (int i = 1; i <= N; i++) {
		scanf("%d", &arr[i]);
		sum += arr[i];
	}

	sort(arr + 1, arr + 1 + N);

	ll ans = sum;
	for (int i = 1; i < N; i++) {
		ans += sum;
		sum -= arr[i];
	}
	printf("%lld\n", ans);
	return 0;
}
