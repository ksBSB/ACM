#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main () {
	int a, b;
	while (scanf("%d%d", &a, &b) == 2 && a + b) {
		int s = 0;

		if (a != b) {
			int x = max(a, b);
			int y = min(a, b);

			while (true) {
				if (x / y > 1)
					break;
				x = x%y;
				swap(x, y);
				s = 1 - s;
			}
		}
		printf("%s wins\n", s ? "Ollie" : "Stan");
	}
	return 0;
}
