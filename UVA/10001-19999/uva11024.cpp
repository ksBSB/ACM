/********************
 * A + C = a + k1 * p
 * B + C = b + k2 * p
 * A + D = c + k3 * p
 * B + D = d + k4 * p
 *
 * a - b - c + d + (k1 - k2 - k3 + k4) * p
 *  = 0;
********************/



#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 5;

int s[maxn][maxn], p[maxn][maxn];

inline int gcd (int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		for (int i  = 1; i <= 2; i++)
			scanf("%d %d %d %d", &s[i][1], &s[i][2], &p[i][1], &p[i][2]);

		int P = p[1][1];
		for (int i = 1; i <= 2; i++)
			for (int j = 1; j <= 2; j++)
				P = gcd(P, p[i][j]);

		int sum = 0;
		for (int i = 1; i <= 2; i++) {
			for (int j = 1; j <= 2; j++) {
				s[i][j] = P - s[i][j] % P;
				if (i == j)
					sum += s[i][j];
				else
					sum -= s[i][j];
			}
		}
		printf("%s\n", sum % P == 0 ? "Yes" : "No");
	}
	return 0;
}
