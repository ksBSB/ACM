#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 105;
int c[N];

int main () {
	char str[N];
	gets(str);
	memset(c, 0, sizeof(c));

	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		c[str[i]-'a']++;
	}

	int ans = N;
	ans = min(c['e'-'a'] / 3, ans);
	ans = min(c['i'-'a'], ans);
	ans = min(c['t'-'a'], ans);
	int t = 'n' - 'a';
	if (c[t] >= 3)
		ans = min((c[t] - 3)/2 + 1, ans);
	else ans = 0;
	printf("%d\n", ans);
	return 0;
}
