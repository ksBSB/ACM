#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;
const int maxn = 105;
typedef long long ll;

int n, arr[maxn];

set<int> vec;

int main () {
	while (scanf("%d", &n) == 1) {
		vec.clear();
		for (int i = 1; i <= n; i++) {
			scanf("%d", &arr[i]);
			for (int j = 1; j < i; j++)
				vec.insert(arr[j] + arr[i]);
		}

		ll ans = 0;;
		for (set<int>::iterator i = vec.begin(); i != vec.end(); i++)
			ans += *i;
		printf("%I64d\n", ans);
	}
	return 0;
}
