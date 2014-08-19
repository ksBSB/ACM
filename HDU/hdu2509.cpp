#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 50;

int main () {
	int ret = 0, n, x;
	while (scanf("%d", &n) == 1) {
		bool flag = false;
		for (int i = 0; i < n; i++) {
			scanf("%d", &x);
			ret ^= x;
			if (x > 1)
				flag = true;
		}

		if (flag) 
			printf("%s\n", ret ? "Yes" : "No");
		else
			printf("%s\n", n&1 ? "No" : "Yes");
	}
	return 0;
}
