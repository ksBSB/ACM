#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;
const int N = 105;

int n, cx[N], cy[N];

int main () {
	int nx = 0, ny = 0, xi, yi;
	memset(cx, 0, sizeof(cx));
	memset(cy, 0, sizeof(cy));

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &xi, &yi);
		if (cx[xi] == 0) nx++;
		if (cy[yi] == 0) ny++;
		cx[xi]++; cy[yi]++;
	}
	printf("%d\n", min(nx, ny));
	return 0;
}
