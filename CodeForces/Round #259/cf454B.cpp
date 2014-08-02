#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5+5;

int n, num[maxn], ans, id;

void init () {
	ans = maxn;
	bool flag = false;

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &num[i]);
		if (num[i] < ans || (flag && num[i] == ans)) {
			ans = num[i];
			id = i;
			flag = false;
		} else if (num[i] > ans)
			flag = true;
	}
}

int solve () {

	for (int i = 1; i < n; i++) {
		if (ans > num[(i+id)%n])
			return -1;
		ans = num[(i+id)%n];
	}

	return id == 0 ? 0 : n - id;
}

int main () {
	init();
	printf("%d\n", solve());
	return 0;
}
