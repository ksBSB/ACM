#include <stdio.h>
#include <iostream>

using namespace std;
typedef long long ll;
const char sign[3] = {'A', 'B', 'C' };

int k, n, m;
ll x;

int count(int c, int pre, int end) {
	if (pre != 0) c--;
	if (end != 2) c--;
	return c / 2;
}

bool judge(ll p, ll q, char fpre, char fend, char spre, char send) {
	for (int i = 3; i <= k; i++) {
		ll t = p + q;
		char ch = fpre;
		if (fend == 'A' && spre == 'C') t++;

		p = q; fpre = spre; fend = send;
		q = t; spre = ch;
	}
	return q == x;
}

void put(int c, int s, int pre, int end) {
	printf("%c", sign[pre]);
	if (s == 1) return;
	s--;

	if (c && pre == 0) {
		printf("C"); c--; s--;
	}

	for (int i = 0; i < c; i++) printf("AC");
	s -= 2 * c;
	for (int i = 1; i < s; i++) printf("B");
	if (s) printf("%c", sign[end]);
}

bool solve() {

	for (int fpre = 0; fpre < 3; fpre++) {
		for (int fend = 0; fend < 3; fend++) {
			if (n == 1 && fpre != fend) continue;
			for (int spre = 0; spre < 3; spre++) {
				for (int send = 0; send < 3; send++) {
					if (m == 1 && spre != send) continue;

					int p = count(n, fpre, fend), q = count(m, spre, send);
					for (int i = 0; i <= p; i++) {
						for (int j = 0; j <= q; j++) {
							if (judge(i, j, sign[fpre], sign[fend], sign[spre], sign[send])) {
								put(i, n, fpre, fend); printf("\n");
								put(j, m, spre, send); printf("\n");
								return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}

int main() {
	scanf("%d", &k);
	cin >> x;
	scanf("%d%d", &n, &m);
	if (!solve()) printf("Happy new year!\n");
	return 0;
}
