#include <stdio.h>
#include <string.h>

const int N = 1e5+5;
struct state {
	int xi, yi;
}s[N];
int n, m, x, y, z, p;

void cw() {
	for (int i = 0; i < p; i++) {
		int r = s[i].yi;
		int l = n + 1 - s[i].xi;
		s[i].xi = r; s[i].yi = l;
	}
	int t = n;
	n = m; m = t;
}

void hr() {
	for (int i = 0; i < p; i++)
		s[i].yi = m + 1 - s[i].yi;
}

void ccw() {
	for (int i = 0; i < p; i++) {
		int r = m + 1 - s[i].yi;
		int l = s[i].xi;
		s[i].xi = r; s[i].yi = l;
	}
	int t = n;
	n = m; m = t;
}

int main () {
	scanf("%d%d%d%d%d%d", &n, &m, &x, &y, &z, &p);
	for (int i = 0; i < p; i++)
		scanf("%d%d", &s[i].xi, &s[i].yi);

	x %= 4;
	for (int i = 0; i < x; i++) cw();
	y %= 2;
	for (int i = 0; i < y; i++) hr();
	z %= 4;
	for (int i = 0; i < z; i++) ccw();

	for (int i = 0; i < p; i++)
		printf("%d %d\n", s[i].xi, s[i].yi);

	return 0;
}
