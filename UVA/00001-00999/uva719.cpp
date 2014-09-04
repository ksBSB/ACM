#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const  int maxn = 1e4+5;

char s[maxn];

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%s", s);
		int n = strlen(s), p = 0, q = 1;

		while (p < n && q < n) {
			int i;
			for (i = 0; i < n; i++) {
				if (s[(p+i)%n] != s[(q+i)%n])
					break;
			}

			if (s[(p+i)%n] > s[(q+i)%n])
				p = p + i + 1;
			else
				q = q + i + 1;

			if (p == q)
				q++;
		}
		printf("%d\n", min(p, q) + 1);
	}
	return 0;
}
