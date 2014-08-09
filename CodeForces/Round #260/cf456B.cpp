#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5+5;

char s[maxn];

int main () {

	scanf("%s", s);
	int len = strlen(s);

	int ans = 0;
	for (int i = 0; i < len; i++)
		ans = (ans * 10 + s[i] - '0') % 4;
	printf("%d\n", ans == 0 ? 4 : 0);

	return 0;
}
