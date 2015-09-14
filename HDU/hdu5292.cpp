#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int bw[30] = {0, 0, 0, 0, 0, 1, -1, 1, -1, 1, -1, -1, 1, -1, 1, -1, 1, 0, 0, 0, 0, 1, -1, -1, 1};

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		int ret = 0;
		char s[2];
		for (int i = 1; i <= 24; i++) {
			scanf("%s", s);
			if (s[0] == 'w' || s[0] == 'y')
				ret += bw[i];
		}
		printf("Case #%d: %s\n", kcas, ret % 3 ? "NO" : "YES");
	}
	return 0;
}
