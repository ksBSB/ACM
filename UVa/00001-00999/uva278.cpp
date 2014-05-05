#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int t[4] = {0, 2, 4, 0};

int m, n;
char ch[20];

int knight() {
	int p = max(n, m);
	int q = min(n, m);

	if (q == 1) {
		return p;
	} else if (q == 2) {
		int s = p / 4;
		int d = p % 4;
		return s * 4 + t[d];
	} else 
		return (n * m + 1) / 2;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%s%d%d", ch, &m, &n);
		if (ch[0] == 'r')
			printf("%d\n", min(m, n));
		else if (ch[0] == 'k')
			printf("%d\n", knight());
		else if (ch[0] == 'Q')
			printf("%d\n", min(m, n));
		else if (ch[0] == 'K')
			printf("%d\n", (n+1)/2 * ((m+1)/2));
	}
	return 0;
}
