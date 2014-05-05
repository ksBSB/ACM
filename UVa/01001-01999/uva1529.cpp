#include <cstdio>
#include <cstring>
#include <cmath>

const int T = 12 * 60 * 100;
const int D = 6545;

int sh, sm, eh, em;

int solve (int s, int t) {
	if (t < s)
		t += T;
	return t / D - (s - 100) / D;
}

int main () {
	printf("Program 3 by team X\n");
	printf("Initial time  Final time  Passes\n");

	while (scanf("%d%d%d%d", &sh, &sm, &eh, &em) == 4) {
		int s = (sh * 60 + sm) * 100;
		int t = (eh * 60 + em) * 100;
		printf("       %02d:%02d       %02d:%02d", sh, sm, eh, em);
		printf("%8d\n", solve(s, t));
	}

	printf("End of program 3 by team X\n");
	return 0;
}
