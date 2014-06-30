#include <stdio.h>
#include <string.h>

const int N = 25;
int n, star, m, max, car[N], order[N][3];

bool judge(int cur) {
    for (int i = order[cur][0]; i < order[cur][1]; i++) {
	car[i] += order[cur][2];
	if (car[i] > n)
	    return false;
    }	
    return true;
}

void find(int cur, int sum) {
    if (cur == m) {
	if (max < sum)
	    max = sum;
	return ;
    }

    int rec[N];
    memcpy(rec, car, sizeof(car));
    find(cur + 1, sum);
    memcpy(car, rec, sizeof(rec));
    if (judge(cur))
	find(cur + 1, sum + order[cur][2] * (order[cur][1] - order[cur][0]));
    memcpy(car, rec, sizeof(rec));
}

int main() {
    while (scanf("%d%d%d", &n, &star, &m), n + m + star) {
	// Init;
	memset(car, 0, sizeof(car));
	memset(order, 0, sizeof(order));
	max = 0;

	// Read;
	for (int i = 0; i < m; i++)
	    for (int j = 0; j < 3; j++ )
		scanf("%d", &order[i][j]);

	find(0, 0);

	printf("%d\n", max);
    }
    return 0;}
