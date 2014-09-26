#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main () {
	int n, c = 0, p, q;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &p, &q);
		if (q - p >= 2) c++;
	}
	printf("%d\n", c);
	return 0;
}
