#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1e5;
const int s = 30;

int n, d, x, rec[maxn+5];
int np, pos[maxn+5];
int a[maxn+5], b[maxn+5];

int get_next () {
	return x = (37LL * x + 10007) % 1000000007;
}

void init_table () {
	for (int i = 0; i < n; i++)
		a[i] = i + 1;

	for (int i = 0; i < n; i++)
		swap(a[i], a[get_next() % (i+1)]);

	for (int i = 0; i < n; i++)
		b[i] = (i < d ? 1 : 0);

	for (int i = 0; i < n; i++)
		swap(b[i], b[get_next() % (i+1)]);
}

void init_pos () {
	np = 0;
	for (int i = 0; i < n; i++) {
		if (b[i])
			pos[np++] = i;
	}

	for (int i = 0; i < n; i++)
		rec[a[i]] = i;
}

int main () {
	scanf("%d%d%d", &n, &d, &x);
	init_table();
	init_pos();

	for (int i = 0; i < n; i++) {
		
		bool flag = true;

		for (int j = n; j >= n-s; j--) {
			if (rec[j] <= i && b[i-rec[j]]) {
				flag = false;
				printf("%d\n", j);
				break;
			}
		}

		if (flag) {
			int ans = 0;
			for (int j = 0; j < np && pos[j] <= i; j++) {
				ans = max(ans, a[i-pos[j]]);
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}
