#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;
const int maxn = 105;

int main () {
	int n, a[maxn], b, c;
	while (scanf("%d%d%d", &n, &b, &c) == 3) {
		for (int i = 0; i < n; i++) scanf("%d", &a[i]);
		int ans = 0;
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
				if (abs(a[i] - a[j]) % b == c) ans++;
		printf("%d\n", ans);
	}
	return 0;
}
