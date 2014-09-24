#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 5 * 1e5 + 5;

int n, arr[maxn];
ll s = 0;
vector<int> vec;

ll solve () {
	if (s % 3)
		return 0;

	s /= 3;
	ll p = 0, ret = 0;
	
	for (int i = 0; i < n; i++) {
		p += arr[i];
		if (p == s)
			vec.push_back(i);
	}

	p = 0;
	for (int i = n-1; i >= 0; i--) {
		p += arr[i];
		if (p == s)
			ret += lower_bound(vec.begin(), vec.end(), i-1) - vec.begin();
	}
	return ret;
}

int main () {
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
		s += arr[i];
	}
	printf("%lld\n", solve());
	return 0;
}
