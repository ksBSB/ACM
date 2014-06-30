#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;
const int N = 1005;

int inN, outN, inData[N][2];
int width, total;
struct state {
	int val, pos;
}outData[N*9];

void init () {
	total = inN = outN = 0;
	
	memset(inData, 0, sizeof(inData));
	int a, b;
	while (scanf("%d%d", &a, &b) == 2) {
		inData[inN][0] = a;
		inData[inN][1] = total;
		total += b;
		if (0 == b) break;
		++inN;
	}
}

int getValue (int pos) {
	int l = 0, r = inN - 1;

	while (l <= r) {
		int mid = (l + r) / 2;
		if (inData[mid][1] <= pos)
			l = mid + 1;
		else
			r = mid - 1;
	}
	return inData[r][0];
}

int cal(int pos) {
	int r = pos / width;
	int l = pos % width;

	int ans = 0;
	for (int i = r - 1; i <= r + 1; i++) {
		for (int j = l - 1; j <= l + 1; j++) {
			int p = i * width + j;
			if (i < 0 || j < 0 || j >= width || p >= total || p == pos)
				continue;
			int t = abs(getValue(p) - getValue(pos));
			ans = max(ans, t);
		}
	}
	return ans;
}

inline bool cmp (const state& a, const state& b) {
	return a.pos < b.pos;
}

void solve () {
	for (int i = 0; i <= inN; i++) {
		int r = inData[i][1] / width;
		int l = inData[i][1] % width;

		for (int j = r - 1; j <= r + 1; j++) {
			for (int k = l - 1; k <= l + 1; k++) {
				int p = j * width + k;
				if (j < 0 || k < 0 || p >= total || p < 0)
					continue;
				outData[outN].val = cal(p);
				outData[outN].pos = p;
				++outN;
			}
		}
	}

	sort (outData, outData + outN, cmp);
	state cur = outData[0];
	for (int i = 0; i < outN; i++) {
		if (cur.val == outData[i].val) continue;

		printf("%d %d\n", cur.val, outData[i].pos - cur.pos);
		cur = outData[i];
	}
	printf("%d %d\n", cur.val, total - cur.pos);
	printf("0 0\n");
}

int main () {
	while (scanf("%d", &width) == 1 && width) {
		init ();
		printf("%d\n", width);
		solve ();
	}
	printf("0\n");
	return 0;
}
