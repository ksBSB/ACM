#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

int x1, x2, y1, y2;
int x3, x4, y3, y4;

bool judge () {
	if (x1 != x2 && y1 != y2) {
		if (abs(x1-x2) != abs(y1-y2))
			return false;

		x3 = x1; y3 = y2;
		x4 = x2; y4 = y1;
		return true;
	} else if (y1 != y2) {
		int d = abs(y1-y2);
		x3 = x1 + d; y3 = y1;
		x4 = x1 + d; y4 = y2;
		return true;
	} else if (x1 != x2) {
		int d = abs(x1-x2);
		x3 = x1; y3 = y1 + d;
		x4 = x2; y4 = y2 + d;
		return true;
	}
	return false;
}

int main () {
	scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

	if (judge())
		printf("%d %d %d %d\n", x3, y3, x4, y4);
	else
		printf("-1\n");
	return 0;
}
