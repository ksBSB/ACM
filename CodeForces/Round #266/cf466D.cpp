#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 2005;
const ll mod = 1e9+7;

int N, H, arr[maxn];

int solve () {
	N++;
	ll ret = 1;

	for (int i = 1; i <= N; i++) {
		int t = arr[i] - arr[i-1];

		if (t > 1 || t < -1)
			return 0;
		else if (t == 0)
			ret = ret * (arr[i] + 1) % mod;
		else if (t == -1)
			ret = ret * arr[i-1] % mod;
	}
	return ret;
}

int main() {
	scanf("%d%d", &N, &H);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &arr[i]);
		arr[i] = H - arr[i];
	}
	printf("%d\n", solve());
	return 0;
}
