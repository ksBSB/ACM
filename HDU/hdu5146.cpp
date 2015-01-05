#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1005;
typedef long long ll;
int n, arr[maxn];

bool judge () {
	int k = n / 2;
	for (int i = 0; i <= k; i++)
		if (arr[i] != arr[n-i-1])
			return true;
	return false;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &n);
		ll odd = 0, even = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &arr[i]);
			if (i&1)
				odd += arr[i];
			else
				even += arr[i];
		}
		printf("%s\n", odd == even && judge() ? "Yes" : "No");
	}
	return 0;
}
