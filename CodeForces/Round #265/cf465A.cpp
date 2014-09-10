#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 105;

int n, s[maxn], c[maxn];
char str[maxn];

int main () {
	scanf("%d%s", &n, str);

	int bit = 1;
	for (int i = 0; i < n; i++) {
		s[i] = str[i] - '0';

		c[i] = s[i] + bit;
		bit = c[i] / 2;
		c[i] %= 2;
	}

	int ret = 0;
	for (int i = 0; i < n; i++)
		if (s[i] != c[i])
			ret++;
	printf("%d\n", ret);
	return 0;
}
