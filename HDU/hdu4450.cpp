#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main () {
	int n, s, a;
	while (scanf("%d", &n) == 1 && n) {
		s = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &a);
			s += a * a;
		}
		printf("%d\n", s);
	}
	return 0;
}
