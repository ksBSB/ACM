#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
int main () {
	int n, p, k, i;
	scanf("%d%d%d", &n, &p, &k);
	if (p > k+1) printf("<< ");

	bool flag = false;
	for (i = max(p-k, 1); i <= p+k && i <= n; i++) {
		if (flag) printf(" ");
		if (i == p) printf("(%d)", p);
		else printf("%d", i);
		flag = true;
	}
	i--;

	if (i < n) printf(" >>\n");
	else printf("\n");
	return 0;
}
