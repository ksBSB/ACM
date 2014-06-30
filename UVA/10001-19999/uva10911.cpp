#include <stdio.h>
#include <string.h>
#include <math.h>
const int N = 20;
const int MAX = 1 << 20;

struct state {
	int x;
	int y;
}tmp[N];
int n, vis[N];
double dis[MAX];

void read() {
	char name[N];
	memset(dis, 0, sizeof(dis));
	memset(tmp, 0, sizeof(tmp));
	n = n * 2;
	for (int i = 0; i < n; i++) {
		scanf("%s%d%d", name, &tmp[i].x, &tmp[i].y);
		vis[i] = 1;
	}
}

int change() {
	int sum = 0;
	for (int i = 0; i < n; i++)
		sum = sum * 2 + vis[i];
	return sum;
}

double dist(int a, int b) {
	return sqrt( pow(tmp[a].x - tmp[b].x, 2) + pow(tmp[a].y - tmp[b].y, 2));
}

double solve() {
	int num = change();
	if (num == 0) return 0;
	if (dis[num] > 1e-9) return dis[num];

	double& sum = dis[num];
	sum = MAX;
	for (int i = 0; i < n; i++) {
		if (!vis[i]) continue;
		for (int j = i + 1; j < n; j++) {
			if (!vis[j]) continue;
			vis[i] = vis[j] = 0;
			double p = dist(i, j) + solve();
			if (p - sum < 1e-9) sum = p;
			vis[i] = vis[j] = 1;
		}
	}
	return sum;
}

int main() {
	int cas = 1;
	while (scanf("%d", &n), n) {
		read();
		printf("Case %d: %.2lf\n", cas++, solve());
	}
	return 0;
}
