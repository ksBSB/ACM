#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int sg[] = {0, 0, 1, 1, 2, 0, 3, 1, 1, 0, 3, 3, 2, 2, 4, 0, 5, 2, 2, 3, 3, 0, 1, 1, 3, 0, 2, 1, 1, 0, 4, 5, 2, 7, 4, 0, 1, 1, 2, 0, 3, 1, 1, 0, 3, 3, 2, 2, 4, 4, 5, 5, 2, 3, 3, 0, 1, 1, 3, 0, 2, 1, 1, 0, 4, 5, 3, 7, 4};
const int cir[] = {4, 8, 1, 1, 2, 0, 3, 1, 1, 0, 3, 3, 2, 2, 4, 4, 5, 5, 9, 3, 3, 0, 1, 1, 3, 0, 2, 1, 1, 0, 4, 5, 3, 7, 4};

int SG (int x) {
	if (x < 69) return sg[x];
	x %= 34;
	return cir[x];
}

int main() {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		int n, x, s = 0;
		scanf("%d", &n);
		while (n--) {
			scanf("%d", &x);
			s ^= SG(x);
		}
		printf("%s\n", s ? "Carol" : "Dave");
	}
    return 0;
}
