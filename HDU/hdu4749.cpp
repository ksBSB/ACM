#include <stdio.h>
#include <string.h>

const int N = 1e5+5;
int n, m, k, next[N], x[N], y[N];
int cx[N][30], cy[N][30];

void init () {
    int a;

	memset(cx[0], 0, sizeof(cx[0]));
	memset(cy[0], 0, sizeof(cy[0]));

    for (int i = 1; i <= n; i++) {
		memcpy(cx[i], cx[i-1], sizeof(cx[i-1]));
        scanf("%d", &x[i]);
		cx[i][x[i]]++;
    }

    for (int i = 1; i <= m; i++) {
		memcpy(cy[i], cy[i-1], sizeof(cy[i-1]));
        scanf("%d", &y[i]);
		cy[i][y[i]]++;
    }
}

bool judge (int p, int q, int (*a)[30], int (*b)[30], int tp, int tq) {
	int s = 0;
	for (int i = 1; i < tp; i++)
		s += a[p][i];
	for (int i = 1; i < tq; i++)
		s -= (b[q][i] - b[q-p][i]);
	return s == 0 && a[p][tp] == (b[q][tq] - b[q-p][tq]);
}

void getNext () {
    int j = 0;
    for (int i = 2; i <= m; i++) {
        while (j > 0 && !judge (j+1, i, cy, cy, y[j+1], y[i]))
            j = next[j];

        if (judge (j+1, i, cy, cy, y[j+1], y[i]))
            j++;
        next[i] = j;
    }
}

int KMP () {
    int ans = 0;
    getNext();

    int j = 0;
    for (int i = 1; i <= n; i++) {
        while (j > 0 && !judge (j+1, i, cy, cx, y[j+1], x[i]))
            j = next[j];

        if (judge (j+1, i, cy, cx, y[j+1], x[i]))
            j++;

        if (j == m) {
            ans++;
            j = 0;
        }
    }
    return ans;
}

int main () {
    while (scanf("%d%d%d", &n, &m, &k) == 3) {
        init ();
        printf("%d\n", KMP());
    }
    return 0;
}
