#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int g[10] = {16, 7, 8, 1, 1, 2, 3};

int solve () {
	char s[3];
	int n, ret = 0, v[10];
	memset(v, 0, sizeof(v));

	scanf("%d", &n);
	while (n--) {
		scanf("%s", s);
		int id = s[0] - 'A';
		ret += g[id];
		v[id] = 1;
	}

	if ((v[1] == 0 || v[2] == 0) && ret != 1)
		ret--;
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		int l = solve();
		int r = solve();
		if (l == r)
			printf("tie\n");
		else
			printf("%s\n", l > r ? "red" : "black");
	}
	return 0;
}
