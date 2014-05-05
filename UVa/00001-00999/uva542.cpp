#include <stdio.h>
#include <string.h>
#include <math.h>

const int N = 16;
char name[N + 10][N + 10];
double p[N + 10][N + 10];
double ans[N + 10], rec[N + 10];

void init() {
	for (int i = 1; i <= N; i++)
		scanf("%s", name[i]);

	int c;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++) {
			scanf("%d", &c);
			p[i][j] = c / 100.0;
		}

	for (int i = 1; i <= N; i++)
		ans[i] = 1;

}

int main () {
	int group, tmp, g, s;
	init();
	for (int i = 0; i < 4; i++) {
		group = pow(2, i + 1);
		tmp = group / 2;

		for (int i = 1; i <= N; i++) {
			double c = 0;
			g = (i - 1) / group;

			if ((i - 1) % group < tmp) {
				s = g * group + tmp;
				
			} else {
				s = g * group;
			}
			for (int j = 1; j <= tmp; j++)
				c += ans[i] * p[i][j + s] * ans[j + s];
			rec[i] = c;
		}
		memcpy(ans, rec, sizeof(ans));
	}

	for (int i = 1; i <= N; i++)
		printf("%-10s p=%.2lf%c\n", name[i], ans[i] * 100, '%'); 

	return 0;
}
