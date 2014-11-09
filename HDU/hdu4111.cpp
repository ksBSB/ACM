#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

bool judge (int c, int s) {
	if (c&1 && s > 2)
		return true;

	if (s == 0 || s == 2)
		return c % 3;
	return s&1;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		int n, s = 0, c = 0, x;

		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &x);
			if (x == 1)
				c++;
			else {
				if (s == 0)
					s = x;
				else
					s += x + 1;
			}
		}
		printf("Case #%d: %s\n", kcas, judge(c, s) ? "Alice" : "Bob");
	}
	return 0;
}
