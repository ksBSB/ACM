#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

bool judge () {
	int n, x;
	bool flag = false;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &x);
		if (x > 1)
			flag = true;
	}

	return flag || (n&1);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		bool flag = judge();
		printf("%s\n", flag ? "poopi" : "piloop");
	}
	return 0;
}
