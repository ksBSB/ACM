#include <stdio.h>
#include <string.h>
const int N = 100005;
int n, f[N * 2];

int getfather(int x) {
	return x == f[x] ? x : f[x] = getfather(f[x]);
}

void setfirend(int x, int y) {
	int pf = getfather(x), qf = getfather(y);
	int pe = getfather(x + n), qe = getfather(y + n);

	if (pe == qf || qe == pf) {
		printf("%d\n", -1);
		return;
	}

	f[pf] = qf;
	f[pe] = qe;
}

void setenemies(int x, int y) {
	int pf = getfather(x), qf = getfather(y);
	int pe = getfather(x + n), qe = getfather(y + n);

	if (pf == qf || pe == qe) {
		printf("%d\n", -1);
		return;
	}

	f[pf] = qe;
	f[qf] = pe;
}

void isfirend(int x, int y) {
	int pf = getfather(x), qf = getfather(y);
	printf("%d\n", pf == qf ? 1 : 0);
}

void isenemies(int x, int y) {
	int pf = getfather(x), qe = getfather(y + n);
	printf("%d\n", pf == qe ? 1 : 0);
}

int main () {
	scanf("%d", &n);
	int cas, a, b;
	for (int i = 0; i < n; i++) f[i] = i, f[i + n] = i + n;
	while (scanf("%d%d%d", &cas, &a, &b), cas || a || b) {
		switch(cas) {
			case 1:
				setfirend(a, b);
				break;	
			case 2:
				setenemies(a, b);
				break;
			case 3:
				isfirend(a, b);
				break;
			case 4:
				isenemies(a, b);
				break;
		}
	}
	return 0;
}
