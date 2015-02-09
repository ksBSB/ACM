#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main () {
	int n, s = 0;
	scanf("%d", &n);
	for (int i = 1; i; i++) {
		s += i;
		if (n < s) {
			printf("%d\n", i - 1);
			break;
		} else
			n -= s;
	}
	return 0;
}
