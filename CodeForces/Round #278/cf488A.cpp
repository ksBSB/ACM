#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

bool judge(int n) {
	n = abs(n);
	while (n) {
		if (n % 10 == 8)
			return true;
		n /= 10;
	}
	return false;
}

int main () {
	int a;
	scanf("%d", &a);
	for (int i = 1; i; i++) {
		if (judge(a+i)) {
			printf("%d\n", i);
			break;
		}
	}
	return 0;
}
