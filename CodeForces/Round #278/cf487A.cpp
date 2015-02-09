#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int inf = 0x3f3f3f3f;
int H, A, D;

bool judge (int h, int a, int d) {
	if (a - D <= 0)
		return false;
	if (A - d <= 0)
		return true;

	int ty = (H - 1) / (a - D) + 1;
	int tm = (h - 1) / (A - d) + 1;

	/*
	printf("M:%d %d %d %d\n", H, A, D, tm);
	printf("Y:%d %d %d %d\n", h, a, d, ty);
	*/

	return ty < tm;
}

int main () {
	int hy, ay, dy;
	scanf("%d%d%d", &hy, &ay, &dy);
	scanf("%d%d%d", &H, &A, &D);

	int h, a, d;
	scanf("%d%d%d", &h, &a, &d);

	int ans = inf;
	for (int i = 0; i >= 0; i++) {
		int hval = i * h;
		if (hval >= ans)
			break;

		for (int j = 0; j + ay <= 200; j++) {
			int aval = j * a;
			if (hval + aval >= ans)
				break;

			for (int k = 0; k + dy <= 100; k++) {
				int dval = k * d;
				if (hval + aval + dval >= ans)
					break;

				if (judge(hy + i, ay + j, dy + k))
					ans = hval + aval + dval;
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
