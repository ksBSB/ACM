/******************
 * c为1的个数，s为其他非1的总步数，包括合并。
 * s > 2时，c若为奇数则必胜，为偶数则s为奇数时必胜；
 * s == 2 || s == 0时，c不为3的倍数时必胜
******************/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n, c, s, x;

void init () {
	c = s = 0;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &x);
		if (x == 1)
			c++;
		else if (x > 1)
			s += (x + 1);
	}

	if (s)
		s--;
}

bool judge () {
	if (s > 2)
		return (c&1) || (s&1);
	if (s == 0)
		return c % 3;
	return c % 3;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int k = 1; k <= cas; k++) {
		init();
		printf("Case #%d: %s\n", k, judge() ? "Alice" : "Bob");
	}
	return 0;
}
