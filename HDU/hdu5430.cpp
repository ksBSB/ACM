#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a%b);
}

int main () {
	int cas, n;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &n);
		if (n == 1) printf("1\n");
		else {
			n++;
			int k = n / 2, c = 0;
			for (int i = 1; i <= k; i++)
				if (gcd(i, n) == 1) c++;
			printf("%d\n", 2 * c);
		}
	}
	return 0;
}
