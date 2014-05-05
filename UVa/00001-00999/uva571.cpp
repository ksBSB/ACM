#include <stdio.h>
#define max(a,b) (a)<(b)?(a):(b)

int main() {
	int A, B, a, b, aid;
	while (scanf("%d%d%d", &A, &B, &aid) == 3) {
		a = b = 0;
		while (1) {
			if (b == aid) {
				printf("success\n");
				break;
			}
			else if (b == B) {
				printf("empty B\n");
				b = 0;
			}
			else if (a == 0) {
				printf("fill A\n");
				a = A;
			}
			else {
				printf("pour A B\n");
				int c = max(B - b, a);
				b += c;
				a -= c;
			}
		}
	}
	return 0;
}
