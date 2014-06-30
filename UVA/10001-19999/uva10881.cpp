#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int  N = 10005;
const char dirName[][10] = { "L", "Turning", "R" };

struct Ant {
	int id;
	int p;
	int dir;
	bool operator < (const Ant& c) const {
		return p < c.p;
	}
}before[N], after[N];
int L, T, n, order[N];

void input() {
	scanf("%d%d%d", &L, &T, &n);

	int d;
	char ch;
	for (int i = 0; i < n; i++) {
		scanf("%d %c", &before[i].p, &ch);
		before[i].id = i;
		d = after[i].dir = before[i].dir = (ch == 'L')? -1: 1;
		after[i].p = before[i].p + T * d;
	}
}

void solve() {

	memset(order, 0, sizeof(order));
	sort(before, before + n);
	for (int i = 0; i < n; i++)
		order[before[i].id] = i;

	sort(after, after + n);
	for (int i = 1; i < n; i++)
		if (after[i - 1].p == after[i].p) after[i - 1].dir = after[i].dir = 0;
}

void output() {
	for (int i = 0; i < n; i++) {
		int a = order[i];
		if (after[a].p < 0 || after[a].p > L) printf("Fell off\n");
		else printf("%d %s\n", after[a].p, dirName[after[a].dir + 1]);
	}
	printf("\n");
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		input();

		solve();

		printf("Case #%d:\n", i);
		output();
	}
	return 0;
}
