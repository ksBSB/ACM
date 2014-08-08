#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 50;

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		int ret = 0, n, x;
		scanf("%d", &n);
		bool flag = false;
		for (int i = 0; i < n; i++) {
			scanf("%d", &x);
			ret ^= x;
			if (x > 1)
				flag = true;
		}

		if (flag) 
			printf("%s\n", ret ? "John" : "Brother");
		else
			printf("%s\n", n&1 ? "Brother" : "John");
	}
	return 0;
}
